
#include "renderer_model_instance.h"
#include "renderer_model_instance_ref.h"
#include "renderer_model_instance_readlock.h"
#include "renderer_model_instance_writelock.h"
#include "../renderer_ref.h"
#include "../renderer_writelock.h"
#include "../../gfx/gfx_ref.h"
#include "../../gfx/gfx_writelock.h"
#include "../../core/core.h"
#include "../../core/shared_obj/shared_obj_guard.h"
#include "../../gfx/model/model_instance/model_instance_writelock.h"
#include "../../gfx/model/model_instance/model_instance_ref.h"
#include "../../gfx/model/model_group_instance/model_group_instance_writelock.h"
#include "../../gfx/model/model_group_instance/model_group_instance_ref.h"
#include "../renderer_model_group_instance/renderer_model_group_instance.h"
#include "../renderer_model_group_instance/renderer_model_group_instance_writelock.h"

namespace dragonpoop
{

    //ctor
    renderer_model_instance::renderer_model_instance( gfx_writelock *g, renderer_writelock *r, model_instance_writelock *m ) : shared_obj( g->getCore()->getMutexMaster() )
    {
        this->g = (gfx_ref *)g->getRef();
        this->r = (renderer_ref *)r->getRef();
        this->c = g->getCore();
        this->id = m->getId();
        this->bAlive = 1;
        this->m = (model_instance_ref *)m->getRef();
        this->beenAssetSynced = 0;
        this->beenUpdated = 1;
    }

    //dtor
    renderer_model_instance::~renderer_model_instance( void )
    {
        shared_obj_writelock *l;
        shared_obj_guard g;

        l = g.writeLock( this );
        g.unlock();

        delete this->g;
        delete this->r;
        delete this->m;
    }

    //return core
    core *renderer_model_instance::getCore( void )
    {
        return this->c;
    }

    //returns true if alive
    bool renderer_model_instance::isAlive( void )
    {
        return this->bAlive;
    }

    //generate read lock
    shared_obj_readlock *renderer_model_instance::genReadLock( shared_obj *p, dpmutex_readlock *l )
    {
        return new renderer_model_instance_readlock( (renderer_model_instance *)p, l );
    }

    //generate write lock
    shared_obj_writelock *renderer_model_instance::genWriteLock( shared_obj *p, dpmutex_writelock *l )
    {
        return new renderer_model_instance_writelock( (renderer_model_instance *)p, l );
    }

    //generate ref
    shared_obj_ref *renderer_model_instance::genRef( shared_obj *p, std::shared_ptr<shared_obj_refkernal> *k )
    {
        return new renderer_model_instance_ref( (renderer_model_instance *)p, k );
    }

    //get id
    dpid renderer_model_instance::getId( void )
    {
        return this->id;
    }

    //kill model
    void renderer_model_instance::kill( void )
    {
        this->bAlive = 0;
    }

    //sync assets like groups and materials
    void renderer_model_instance::syncAssets( gfx_writelock *g, renderer_model_instance_writelock *m, renderer_writelock *r, model_instance_writelock *mi )
    {
        mi->setRenderer( m );
        this->makeGroups( g, m, r, mi );
        this->update();
    }

    //run model
    void renderer_model_instance::run( dpthread_lock *thd, renderer_model_instance_writelock *m, renderer_writelock *r )
    {
        gfx_writelock *g;
        model_instance_writelock *mi;
        shared_obj_guard o0, o1;

        if( !this->beenAssetSynced )
        {
            g = (gfx_writelock *)o0.writeLock( this->g );
            mi = (model_instance_writelock *)o1.writeLock( this->m );
            if( g && mi )
            {
                this->syncAssets( g, m, r, mi );
                this->beenAssetSynced = 1;
            }
        }

        if( !this->beenUpdated )
        {
            this->syncGroups( thd, m, r );
            this->beenUpdated = 1;
        }
    }

    //render model instance
    void renderer_model_instance::render( dpthread_lock *thd, renderer_model_instance_writelock *m, renderer_writelock *r )
    {

    }

    //make groups
    void renderer_model_instance::makeGroups( gfx_writelock *g, renderer_model_instance_writelock *m, renderer_writelock *r, model_instance_writelock *mi )
    {
        shared_obj_guard o;
        model_group_instance_ref *p;
        model_group_instance_writelock *pl;
        renderer_model_group_instance *rg;
        std::list<model_group_instance_ref *> l;
        std::list<model_group_instance_ref *>::iterator i;
        dpid pid;

        dpid_zero( &pid );
        mi->getGroupsByParent( pid, &l );

        for( i = l.begin(); i != l.end(); ++i )
        {
            p = *i;
            pl = (model_group_instance_writelock *)o.writeLock( p );
            rg = this->genGroup( g, r, mi, pl );
            if( !rg )
                continue;
            this->groups.push_back( rg );
        }

        mi->releaseGetGroups( &l );
    }

    //kill groups
    void renderer_model_instance::killGroups( renderer_model_instance_writelock *m, renderer_writelock *r )
    {
        std::list<renderer_model_group_instance *> *l, d;
        std::list<renderer_model_group_instance *>::iterator i;
        renderer_model_group_instance *p;

        l = &this->groups;
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

    //run groups
    void renderer_model_instance::runGroups( dpthread_lock *thd, renderer_model_instance_writelock *m, renderer_writelock *r )
    {
        std::list<renderer_model_group_instance *> *l;
        std::list<renderer_model_group_instance *>::iterator i;
        renderer_model_group_instance *p;
        renderer_model_group_instance_writelock *pl;
        shared_obj_guard o;

        l = &this->groups;
        for( i = l->begin(); i != l->end(); ++i )
        {
            p = *i;
            pl = (renderer_model_group_instance_writelock *)o.tryWriteLock( p, 100 );
            if( pl )
                pl->run( thd, m, r );
        }
    }

    //run groups
    void renderer_model_instance::syncGroups( dpthread_lock *thd, renderer_model_instance_writelock *m, renderer_writelock *r )
    {
        std::list<renderer_model_group_instance *> *l;
        std::list<renderer_model_group_instance *>::iterator i;
        renderer_model_group_instance *p;
        renderer_model_group_instance_writelock *pl;
        shared_obj_guard o;

        l = &this->groups;
        for( i = l->begin(); i != l->end(); ++i )
        {
            p = *i;
            pl = (renderer_model_group_instance_writelock *)o.tryWriteLock( p, 100 );
            if( pl )
                pl->sync( thd, m, r );
        }
    }

    //render groups
    void renderer_model_instance::renderGroups( dpthread_lock *thd, renderer_model_instance_writelock *m, renderer_writelock *r )
    {
        std::list<renderer_model_group_instance *> *l;
        std::list<renderer_model_group_instance *>::iterator i;
        renderer_model_group_instance *p;
        renderer_model_group_instance_writelock *pl;
        shared_obj_guard o;

        l = &this->groups;
        for( i = l->begin(); i != l->end(); ++i )
        {
            p = *i;
            pl = (renderer_model_group_instance_writelock *)o.tryWriteLock( p, 100 );
            if( pl )
                pl->render( thd, m, r );
        }
    }

    //generate group from renderer
    renderer_model_group_instance *renderer_model_instance::genGroup( gfx_writelock *g, renderer_writelock *r, model_instance_writelock *m, model_group_instance_writelock *grp )
    {
        return r->genGroup( g, m, grp );
    }

    //forces an update to happen next run cycle
    void renderer_model_instance::update( void )
    {
        this->beenUpdated = 0;
    }

};
