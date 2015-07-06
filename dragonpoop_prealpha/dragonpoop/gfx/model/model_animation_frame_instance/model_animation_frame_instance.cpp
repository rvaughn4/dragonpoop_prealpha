
#include "model_animation_frame_instance.h"
#include "model_animation_frame_instance_readlock.h"
#include "model_animation_frame_instance_writelock.h"
#include "model_animation_frame_instance_ref.h"

namespace dragonpoop
{

    //ctor
    model_animation_frame_instance::model_animation_frame_instance( model_writelock *ml, dpid id, dpid instance_id, dpid animation_frame_id, dpid animation_id, dpid frame_id ) : model_component( ml, id,model_component_type_animation_frame_instance, 0 )
    {
        this->instance_id = instance_id;
        this->animation_frame_id = animation_frame_id;
        this->animation_id = animation_id;
        this->frame_id = frame_id;
    }

    //dtor
    model_animation_frame_instance::~model_animation_frame_instance( void )
    {

    }

    //generate read lock
    shared_obj_readlock *model_animation_frame_instance::genReadLock( shared_obj *p, dpmutex_readlock *l )
    {
        return new model_animation_frame_instance_readlock( (model_animation_frame_instance *)p, l );
    }

    //generate write lock
    shared_obj_writelock *model_animation_frame_instance::genWriteLock( shared_obj *p, dpmutex_writelock *l )
    {
        return new model_animation_frame_instance_writelock( (model_animation_frame_instance *)p, l );
    }

    //generate ref
    shared_obj_ref *model_animation_frame_instance::genRef( shared_obj *p, std::shared_ptr<shared_obj_refkernal> *k )
    {
        return new model_animation_frame_instance_ref( (model_animation_frame_instance *)p, k );
    }

    //do background processing
    void model_animation_frame_instance::onRun( dpthread_lock *thd, gfx_writelock *g, model_writelock *m, model_component_writelock *l )
    {

    }

    //return instance id
    dpid model_animation_frame_instance::getInstanceId( void )
    {
        return this->instance_id;
    }

    //return animation frame id
    dpid model_animation_frame_instance::getAnimationFrameId( void )
    {
        return this->animation_frame_id;
    }

    //return animation id
    dpid model_animation_frame_instance::getAnimationId( void )
    {
        return this->animation_id;
    }

    //return frame id
    dpid model_animation_frame_instance::getFrameId( void )
    {
        return this->frame_id;
    }

};
