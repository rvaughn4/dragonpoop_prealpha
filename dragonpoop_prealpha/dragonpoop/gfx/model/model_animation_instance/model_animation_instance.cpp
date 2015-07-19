
#include "model_animation_instance.h"
#include "model_animation_instance_readlock.h"
#include "model_animation_instance_writelock.h"
#include "model_animation_instance_ref.h"

namespace dragonpoop
{

    //ctor
    model_animation_instance::model_animation_instance( model_writelock *ml, dpid id, dpid instance_id, dpid animation_id ) : model_component( ml, id,model_component_type_animation_instance, 0 )
    {
        this->instance_id = instance_id;
        this->animation_id = animation_id;
        this->findMaxTime();
    }

    //dtor
    model_animation_instance::~model_animation_instance( void )
    {

    }

    //generate read lock
    shared_obj_readlock *model_animation_instance::genReadLock( shared_obj *p, dpmutex_readlock *l )
    {
        return new model_animation_instance_readlock( (model_animation_instance *)p, l );
    }

    //generate write lock
    shared_obj_writelock *model_animation_instance::genWriteLock( shared_obj *p, dpmutex_writelock *l )
    {
        return new model_animation_instance_writelock( (model_animation_instance *)p, l );
    }

    //generate ref
    shared_obj_ref *model_animation_instance::genRef( shared_obj *p, std::shared_ptr<shared_obj_refkernal> *k )
    {
        return new model_animation_instance_ref( (model_animation_instance *)p, k );
    }

    //do background processing
    void model_animation_instance::onRun( dpthread_lock *thd, gfx_writelock *g, model_writelock *m, model_component_writelock *l )
    {

    }

    //return instance id
    dpid model_animation_instance::getInstanceId( void )
    {
        return this->instance_id;
    }

    //return vertex id
    dpid model_animation_instance::getAnimationId( void )
    {
        return this->animation_id;
    }

    //find last frame time
    void model_animation_instance::findMaxTime( void )
    {
    }

    //get props from animation
    void model_animation_instance::findProps( void )
    {
        model_animation_ref *r;
        model_animation_readlock *rl;
        shared_obj_guard o;
    }

};
