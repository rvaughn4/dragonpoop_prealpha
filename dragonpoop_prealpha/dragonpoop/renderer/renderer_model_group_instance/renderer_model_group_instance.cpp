
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
#include "../../gfx/model/model_group_instance/model_group_instance_ref.h"

namespace dragonpoop
{

    //ctor
    renderer_model_group_instance::renderer_model_group_instance( gfx_writelock *g, renderer_writelock *r, model_group_instance_writelock *grp ) : shared_obj( g->getCore()->getMutexMaster() )
    {
        this->g = (gfx_ref *)g->getRef();
        this->r = (renderer_ref *)r->getRef();
        this->c = g->getCore();
        this->id = grp->getId();
        this->instance_id = grp->getInstanceId();
        this->bAlive = 1;
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

    //run model
    void renderer_model_group_instance::run( dpthread_lock *thd, renderer_model_group_instance_writelock *m, renderer_writelock *r )
    {

    }

    //return instance id
    dpid renderer_model_group_instance::getInstanceId( void )
    {
        return this->instance_id;
    }

    //generate group from renderer
    renderer_model_group_instance *renderer_model_group_instance::genGroup( gfx_writelock *g, renderer_writelock *r, model_group_instance_writelock *grp )
    {
        return 0;
    }

};
