
#include "renderer.h"
#include "../core/core.h"
#include "../core/dptask/dptasks.h"
#include "renderer_task.h"
#include "renderer_readlock.h"
#include "renderer_writelock.h"
#include "renderer_ref.h"
#include "../core/dpthread/dpthread_lock.h"
#include "../core/dptaskpool/dptaskpool_writelock.h"
#include "renderer_model_instance/renderer_model_instance.h"
#include "renderer_model_instance/renderer_model_instance_ref.h"
#include "renderer_model_instance/renderer_model_instance_writelock.h"
#include "renderer_model_group_instance/renderer_model_group_instance.h"
#include "../core/shared_obj/shared_obj_guard.h"
#include "../gfx/gfx_writelock.h"
#include "../gfx/gfx_ref.h"
#include "../gfx/model/model_instance/model_instance_ref.h"
#include "../gfx/model/model_instance/model_instance_writelock.h"

#include <iostream>
#include <thread>

namespace dragonpoop
{

    //ctor
    renderer::renderer( core *c, dptaskpool_writelock *tp ) : shared_obj( c->getMutexMaster() )
    {
        this->c = c;
        this->bDoRun = 1;
        this->bIsRun = 0;
        this->gtsk = new renderer_task( this );
        this->tsk = new dptask( c->getMutexMaster(), this->gtsk, 3, 1 );
        tp->addTask( this->tsk );
    }

    //dtor
    renderer::~renderer( void )
    {
        this->_kill();
        this->killModels();
        delete this->tsk;
        delete this->gtsk;
    }

    //stop task and deinit api
    void renderer::_kill( void )
    {
        volatile bool d;

        this->bDoRun = 0;
        d = this->bIsRun;
        while( d )
        {
            std::this_thread::sleep_for( std::chrono::milliseconds( 1 ) );
            d = this->bIsRun;
        }
    }

    //returns true if running
    bool renderer::isRunning( void )
    {
        if( !this->tsk )
            return 0;
        return this->bIsRun;
    }

    //return core
    core *renderer::getCore( void )
    {
        return this->c;
    }

    //generate read lock
    shared_obj_readlock *renderer::genReadLock( shared_obj *p, dpmutex_readlock *l )
    {
        return new renderer_readlock( (renderer *)p, l );
    }

    //generate write lock
    shared_obj_writelock *renderer::genWriteLock( shared_obj *p, dpmutex_writelock *l )
    {
        return new renderer_writelock( (renderer *)p, l );
    }

    //generate ref
    shared_obj_ref *renderer::genRef( shared_obj *p, std::shared_ptr<shared_obj_refkernal> *k )
    {
        return new renderer_ref( (renderer *)p, k );
    }

    //stop renderer task
    void renderer::kill( void )
    {
        this->bDoRun = 0;
    }

    //run renderer from task
    void renderer::run( dptask_writelock *tskl, dpthread_lock *thd, renderer_writelock *r )
    {
        uint64_t t;
        gfx_writelock *g;
        gfx_ref *gr;
        shared_obj_guard o;

        if( this->bIsRun )
        {
            if( !this->bDoRun )
            {
                this->deinitApi();
                this->bIsRun = 0;
                tskl->kill();
                return;
            }

            t = thd->getTicks();
            if( t - this->lastMakeModel > 300 )
            {
                gr = this->getCore()->getGfx();
                g = (gfx_writelock *)o.writeLock( gr );
                delete gr;
                this->makeModels( g, r );
                this->lastMakeModel = t;
            }
            this->runModels( thd, r );

            if( !this->runApi() )
                this->bDoRun = 0;
            else
            {
                this->setViewport( this->getWidth(), this->getHeight() );
#define randcolor (float)rand() / (float)RAND_MAX
                this->clearScreen( randcolor, randcolor, randcolor );
                this->prepareWorldRender();
                this->renderModels( thd, r );

                this->prepareGuiRender();
                this->flipBuffer();
            }
            return;
        }

        if( !this->bDoRun )
        {
            tskl->kill();
            return;
        }

        if( this->initApi() )
            this->bIsRun = 1;
        else
            this->bDoRun = 0;
    }

    //init graphics api
    bool renderer::initApi( void )
    {
        return 1;
    }

    //deinit graphics api
    void renderer::deinitApi( void )
    {
    }

    //do background graphics api processing
    bool renderer::runApi( void )
    {
        return 1;
    }

    //generate model instance
    renderer_model_instance *renderer::genModel( gfx_writelock *g, renderer_writelock *r, model_instance_writelock *m )
    {
        return new renderer_model_instance( g, r, m );
    }

    //generate model group instance
    renderer_model_group_instance *renderer::genGroup( gfx_writelock *g, renderer_writelock *r, model_instance_writelock *m, model_group_instance_writelock *grp )
    {
        return new renderer_model_group_instance( g, r, m, grp );
    }

    //make model instances
    void renderer::makeModels( gfx_writelock *g, renderer_writelock *r )
    {
        shared_obj_guard o;
        model_instance_ref *p;
        model_instance_writelock *pl;
        renderer_model_instance *rg;
        std::list<model_instance_ref *> l;
        std::list<model_instance_ref *>::iterator i;

        g->getInstances( &l );

        for( i = l.begin(); i != l.end(); ++i )
        {
            p = *i;
            pl = (model_instance_writelock *)o.tryWriteLock( p, 100 );
            if( !pl )
                continue;
            if( pl->hasRenderer() )
                continue;
            rg = this->genModel( g, r, pl );
            if( !rg )
                continue;
            this->models.push_back( rg );
        }

        g->releaseGetInstances( &l );
    }

    //kill model instances
    void renderer::killModels( void )
    {
        std::list<renderer_model_instance *> *l, d;
        std::list<renderer_model_instance *>::iterator i;
        renderer_model_instance *p;

        l = &this->models;
        for( i = l->begin(); i != l->end(); ++i )
        {
            p = *i;
            d.push_back( p );
        }
        l->clear();

        l = &d;
        for( i = l->begin(); i != l->end(); ++i )
        {
            p = *i;
            delete p;
        }
        l->clear();
    }

    //run model instances
    void renderer::runModels( dpthread_lock *thd, renderer_writelock *r )
    {
        std::list<renderer_model_instance *> *l, d;
        std::list<renderer_model_instance *>::iterator i;
        renderer_model_instance *p;
        renderer_model_instance_writelock *pl;
        shared_obj_guard o;

        l = &this->models;
        for( i = l->begin(); i != l->end(); ++i )
        {
            p = *i;
            pl = (renderer_model_instance_writelock *)o.tryWriteLock( p, 100 );
            if( !pl )
                continue;
            pl->run( thd, r );
            if( !pl->isAlive() )
                d.push_back( p );
        }
        o.unlock();

        l = &d;
        for( i = l->begin(); i != l->end(); ++i )
        {
            p = *i;
            delete p;
        }
        l->clear();
    }

    //render model instances
    void renderer::renderModels( dpthread_lock *thd, renderer_writelock *r )
    {
        std::list<renderer_model_instance *> *l, d;
        std::list<renderer_model_instance *>::iterator i;
        renderer_model_instance *p;
        renderer_model_instance_writelock *pl;
        shared_obj_guard o;

        l = &this->models;
        for( i = l->begin(); i != l->end(); ++i )
        {
            p = *i;
            pl = (renderer_model_instance_writelock *)o.tryWriteLock( p, 100 );
            if( pl )
                pl->render( thd, r );
        }
        o.unlock();
    }

};
