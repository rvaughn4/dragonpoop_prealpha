
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

namespace dragonpoop
{

    //ctor
    renderer_model_instance::renderer_model_instance( gfx_writelock *g, renderer_writelock *r, dpid id ) : shared_obj( g->getCore()->getMutexMaster() )
    {
        this->g = (gfx_ref *)g->getRef();
        this->r = (renderer_ref *)r->getRef();
        this->id = id;
        this->bAlive = 1;
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

    //run model
    void renderer_model_instance::run( dpthread_lock *thd, renderer_model_instance_writelock *m )
    {

    }

};
