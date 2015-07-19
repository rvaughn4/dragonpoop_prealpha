
#include "renderer_model_group_instance.h"
#include "renderer_model_group_instance_ref.h"
#include "renderer_model_group_instance_readlock.h"
#include "renderer_model_group_instance_writelock.h"
#include "../renderer_ref.h"
#include "../renderer_writelock.h"
#include "../../gfx/gfx_ref.h"
#include "../../gfx/gfx_writelock.h"
#include "../../core/core.h"
#include "../../core/shared_obj/shared_obj_guard.h"
#include "../../gfx/model/model_group_instance/model_group_instance_writelock.h"
#include "../../gfx/model/model_group_instance/model_group_instance_readlock.h"
#include "../../gfx/model/model_group_instance/model_group_instance_ref.h"
#include "../../gfx/model/model_instance/model_instance_writelock.h"
#include "../../gfx/model/model_instance/model_instance_ref.h"

namespace dragonpoop
{

    //ctor
    renderer_model_group_instance::renderer_model_group_instance( gfx_writelock *g, renderer_writelock *r, model_instance_writelock *m, model_group_instance_writelock *grp ) : shared_obj( g->getCore()->getMutexMaster() )
    {
        this->g = (gfx_ref *)g->getRef();
        this->r = (renderer_ref *)r->getRef();
        this->c = g->getCore();
        this->id = grp->getId();
        this->m = (model_instance_ref *)m->getRef();
        this->instance_id = grp->getInstanceId();
        this->bAlive = 1;
        this->beenAssetSynced = 0;
        this->grp = (model_group_instance_ref *)grp->getRef();
    }

    //dtor
    renderer_model_group_instance::~renderer_model_group_instance( void )
    {
        shared_obj_writelock *l;
        shared_obj_guard g;

        l = g.writeLock( this );
        g.unlock();

        delete this->g;
        delete this->r;
        delete this->grp;
        delete this->m;
    }

    //return core
    core *renderer_model_group_instance::getCore( void )
    {
        return this->c;
    }

    //returns true if alive
    bool renderer_model_group_instance::isAlive( void )
    {
        return this->bAlive;
    }

    //generate read lock
    shared_obj_readlock *renderer_model_group_instance::genReadLock( shared_obj *p, dpmutex_readlock *l )
    {
        return new renderer_model_group_instance_readlock( (renderer_model_group_instance *)p, l );
    }

    //generate write lock
    shared_obj_writelock *renderer_model_group_instance::genWriteLock( shared_obj *p, dpmutex_writelock *l )
    {
        return new renderer_model_group_instance_writelock( (renderer_model_group_instance *)p, l );
    }

    //generate ref
    shared_obj_ref *renderer_model_group_instance::genRef( shared_obj *p, std::shared_ptr<shared_obj_refkernal> *k )
    {
        return new renderer_model_group_instance_ref( (renderer_model_group_instance *)p, k );
    }

    //get id
    dpid renderer_model_group_instance::getId( void )
    {
        return this->id;
    }

    //kill model
    void renderer_model_group_instance::kill( void )
    {
        this->bAlive = 0;
    }

    //run group
    void renderer_model_group_instance::run( dpthread_lock *thd, renderer_model_instance_writelock *m, renderer_model_group_instance_writelock *grp, renderer_writelock *r )
    {
        gfx_writelock *g;
        model_group_instance_writelock *mi;
        shared_obj_guard o0, o1;

        if( !this->beenAssetSynced )
        {
            g = (gfx_writelock *)o0.tryWriteLock( this->g, 10 );
            if( g )
            {
                mi = (model_group_instance_writelock *)o1.tryWriteLock( this->grp, 10 );
                if( mi )
                {
                    this->syncAssets( g, m, grp, r, mi );
                    this->beenAssetSynced = 1;
                }
            }
        }
    }

    //run group
    void renderer_model_group_instance::sync( dpthread_lock *thd, renderer_model_instance_writelock *m, renderer_model_group_instance_writelock *grp, renderer_writelock *r )
    {
        model_group_instance_readlock *gl;
        shared_obj_guard o;

        gl = (model_group_instance_readlock *)o.tryReadLock( this->grp, 10 );
        if( !gl )
            return;
        this->vb.clear();
        gl->getVertexes( &this->vb );

        this->syncGroups( thd, m, r );
    }

    //render group
    void renderer_model_group_instance::render( dpthread_lock *thd, renderer_model_instance_readlock *m, renderer_model_group_instance_readlock *grp, renderer_writelock *r )
    {
        r->renderGroup( m, grp );
        this->renderGroups( thd, m, r );
    }

    //return instance id
    dpid renderer_model_group_instance::getInstanceId( void )
    {
        return this->instance_id;
    }

    //generate group from renderer
    renderer_model_group_instance *renderer_model_group_instance::genGroup( gfx_writelock *g, renderer_writelock *r, model_instance_writelock *m, model_group_instance_writelock *grp )
    {
        return r->genGroup( g, m, grp );
    }

    //sync assets like groups and materials
    void renderer_model_group_instance::syncAssets( gfx_writelock *g, renderer_model_instance_writelock *m, renderer_model_group_instance_writelock *gl, renderer_writelock *r, model_group_instance_writelock *grp )
    {
        grp->setRenderer( gl );
        this->makeGroups( g, m, r, grp );
    }

    //make groups
    void renderer_model_group_instance::makeGroups( gfx_writelock *g, renderer_model_instance_writelock *m, renderer_writelock *r, model_group_instance_writelock *grp )
    {
        shared_obj_guard o, o1;
        model_group_instance_ref *p;
        model_group_instance_writelock *pl;
        renderer_model_group_instance *rg;
        std::list<model_group_instance_ref *> l;
        std::list<model_group_instance_ref *>::iterator i;
        model_instance_writelock *mi;

        mi = (model_instance_writelock *)o1.readLock( this->m );
        if( !mi )
            return;

        mi->getGroupsByParent( this->id, &l );

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
    void renderer_model_group_instance::killGroups( renderer_model_instance_writelock *m, renderer_writelock *r )
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
    void renderer_model_group_instance::runGroups( dpthread_lock *thd, renderer_model_instance_writelock *m, renderer_writelock *r )
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
            pl = (renderer_model_group_instance_writelock *)o.tryWriteLock( p, 10 );
            if( pl )
                pl->run( thd, m, r );
        }
    }

    //sync groups
    void renderer_model_group_instance::syncGroups( dpthread_lock *thd, renderer_model_instance_writelock *m, renderer_writelock *r )
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
            pl = (renderer_model_group_instance_writelock *)o.tryWriteLock( p, 10 );
            if( pl )
                pl->sync( thd, m, r );
        }
    }

    //render groups
    void renderer_model_group_instance::renderGroups( dpthread_lock *thd, renderer_model_instance_readlock *m, renderer_writelock *r )
    {
        std::list<renderer_model_group_instance *> *l;
        std::list<renderer_model_group_instance *>::iterator i;
        renderer_model_group_instance *p;
        renderer_model_group_instance_readlock *pl;
        shared_obj_guard o;

        l = &this->groups;
        for( i = l->begin(); i != l->end(); ++i )
        {
            p = *i;
            pl = (renderer_model_group_instance_readlock *)o.tryReadLock( p, 10 );
            if( pl )
                pl->render( thd, m, r );
        }
    }

    //returns pointer to vertex buffer
    dpvertexindex_buffer *renderer_model_group_instance::getBuffer( void )
    {
        return &this->vb;
    }

};
