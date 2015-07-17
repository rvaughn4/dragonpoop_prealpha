
#include "gfx.h"
#include "../core/core.h"
#include "../core/dptask/dptasks.h"
#include "gfx_task.h"
#include "gfx_readlock.h"
#include "gfx_writelock.h"
#include "gfx_ref.h"
#include "../core/dpthread/dpthread_lock.h"
#include "../core/dptaskpool/dptaskpool_writelock.h"
#include "../renderer/renderer.h"
#include "../renderer/openglx_1o5_renderer/openglx_1o5_renderer.h"
#include "../core/shared_obj/shared_obj_guard.h"
#include "model/model.h"
#include "model/model_ref.h"
#include "model/model_writelock.h"
#include "model/model_readlock.h"
#include "model/model_instance/model_instance_ref.h"

#include <iostream>

namespace dragonpoop
{

    //ctor
    gfx::gfx( core *c, dptaskpool_writelock *tp ) : shared_obj( c->getMutexMaster() )
    {
        this->c = c;
        this->r = 0;
        this->gtsk = new gfx_task( this );
        this->tsk = new dptask( c->getMutexMaster(), this->gtsk, 100, 0 );
        tp->addTask( this->tsk );
        this->r = new openglx_1o5_renderer( c, tp );
    }

    //dtor
    gfx::~gfx( void )
    {
        this->kill();
        this->deleteModels();
        delete this->r;
        this->r = 0;
        delete this->gtsk;
    }

    //returns true if running
    bool gfx::isRunning( void )
    {
        if( !this->tsk )
            return 0;
        return this->tsk->isLinked();
    }

    //return core
    core *gfx::getCore( void )
    {
        return this->c;
    }

    //generate read lock
    shared_obj_readlock *gfx::genReadLock( shared_obj *p, dpmutex_readlock *l )
    {
        return new gfx_readlock( (gfx *)p, l );
    }

    //generate write lock
    shared_obj_writelock *gfx::genWriteLock( shared_obj *p, dpmutex_writelock *l )
    {
        return new gfx_writelock( (gfx *)p, l );
    }

    //generate ref
    shared_obj_ref *gfx::genRef( shared_obj *p, std::shared_ptr<shared_obj_refkernal> *k )
    {
        return new gfx_ref( (gfx *)p, k );
    }

    //stop gfx task
    void gfx::kill( void )
    {
        dptask_writelock *tl;
        shared_obj_guard o;

        if( !this->tsk )
            return;

        tl = (dptask_writelock *)o.writeLock( this->tsk );
        tl->kill();
        o.unlock();

        delete this->tsk;
        this->tsk = 0;
    }

    //run gfx from task
    void gfx::run( dpthread_lock *thd, gfx_writelock *g )
    {
        this->runModels( thd, g );
    }

    //run all models
    void gfx::runModels( dpthread_lock *thd, gfx_writelock *g )
    {
        model *m;
        std::list<model *> *l, d;
        std::list<model *>::iterator i;
        shared_obj_guard o;
        model_writelock *ml;

        l = &this->models;
        for( i = l->begin(); i != l->end(); ++i )
        {
            m = *i;
            if( !m->isAlive() )
                d.push_back( m );
            ml = (model_writelock *)o.tryWriteLock( m, 100 );
            if( ml )
                ml->run( thd, g );
        }

        l = &d;
        for( i = l->begin(); i != l->end(); ++i )
        {
            m = *i;
            this->models.remove( m );
            this->model_tree.removeLeaf( (void *)m );
        }
        l->clear();
    }

    //delete all models
    void gfx::deleteModels( void )
    {
        model *m;
        std::list<model *> *l, d;
        std::list<model *>::iterator i;

        l = &this->models;
        for( i = l->begin(); i != l->end(); ++i )
        {
            m = *i;
            d.push_back( m );
        }
        l->clear();
        this->model_tree.clear();

        l = &d;
        for( i = l->begin(); i != l->end(); ++i )
        {
            m = *i;
            delete m;
        }
        l->clear();
    }

    //find model by id
    model_ref *gfx::findModel( dpid id )
    {
        shared_obj_guard o;
        model *m;
        model_writelock *ml;

        m = (model *)this->model_tree.findLeaf( id );
        if( !m )
            return 0;
        ml = (model_writelock *)o.writeLock( m );
        if( !ml )
            return 0;
        return (model_ref *)ml->getRef();
    }

    //find model by name
    model_ref *gfx::findModel( const char *c )
    {
        shared_obj_guard o;
        model *m;
        model_writelock *ml;
        model_readlock *mrl;
        std::list<model *> *l;
        std::list<model *>::iterator i;
        std::string s;

        l = &this->models;
        for( i = l->begin(); i != l->end(); ++i )
        {
            m = *i;
            mrl = (model_readlock *)o.readLock( m );
            if( !mrl )
                continue;
            mrl->getName( &s );
            if( s.compare( c ) != 0 )
                continue;
            ml = (model_writelock *)o.writeLock( m );
            if( !ml )
                return 0;
            return (model_ref *)ml->getRef();
        }

        return 0;
    }

    //create model
    model_ref *gfx::createModel( dpthread_lock *thd, gfx_writelock *g )
    {
        return this->createModel( thd, g, thd->genId(), "New Model" );
    }

    //create model having name
    model_ref *gfx::createModel( dpthread_lock *thd, gfx_writelock *g, const char *cname )
    {
        return this->createModel( thd, g, thd->genId(), cname );
    }

    //create model having id
    model_ref *gfx::createModel( dpthread_lock *thd, gfx_writelock *g, dpid id )
    {
        return this->createModel( thd, g, id, "New Model" );
    }

    //create model having id and name
    model_ref *gfx::createModel( dpthread_lock *thd, gfx_writelock *g, dpid id, const char *cname )
    {
        shared_obj_guard o;
        model *m;
        model_writelock *ml;

        m = new model( g, id, cname );
        if( !m )
            return 0;
        this->models.push_back( m );
        this->model_tree.addLeaf( id, (void *)m );

        ml = (model_writelock *)o.writeLock( m );
        if( !ml )
            return 0;
        return (model_ref *)ml->getRef();
    }

    //get model instances
    unsigned int gfx::getInstances( std::list<model_instance_ref *> *ll )
    {
        std::list<model *> *l;
        std::list<model *>::iterator i;
        model *p;
        unsigned int r;
        shared_obj_guard o;
        model_readlock *pl;

        l = &this->models;
        r = 0;
        for( i = l->begin(); i != l->end(); ++i )
        {
            p = *i;
            pl = (model_readlock *)o.readLock( p );
            if( !pl )
                continue;
            r += pl->getInstances( ll );
        }

        return r;
    }

    //release list returned by getInstances()
    void gfx::releaseGetInstances( std::list<model_instance_ref *> *l )
    {
        std::list<model_instance_ref *>::iterator i;
        model_instance_ref *p;

        for( i = l->begin(); i != l->end(); ++i )
        {
            p = *i;
            delete p;
        }
        l->clear();
    }

};
