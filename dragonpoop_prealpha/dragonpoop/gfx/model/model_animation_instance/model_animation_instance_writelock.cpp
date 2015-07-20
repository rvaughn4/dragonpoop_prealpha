
#include "model_animation_instance_writelock.h"
#include "model_animation_instance.h"

namespace dragonpoop
{

    //ctor
    model_animation_instance_writelock::model_animation_instance_writelock( model_animation_instance *t, dpmutex_writelock *l ) : model_component_writelock( t, l )
    {
        this->t = t;
    }

    //dtor
    model_animation_instance_writelock::~model_animation_instance_writelock( void )
    {

    }

    //return instance id
    dpid model_animation_instance_writelock::getInstanceId( void )
    {
        return this->t->getInstanceId();
    }

    //return animation id
    dpid model_animation_instance_writelock::getAnimationId( void )
    {
        return this->t->getAnimationId();
    }

    //sync animation
    void model_animation_instance_writelock::sync( dpthread_lock *thd, model_writelock *ml )
    {
        this->t->sync( thd, ml );
    }

    //return current frame
    dpid model_animation_instance_writelock::getCurrentFrameId( void )
    {
        return this->t->getCurrentFrameId();
    }

    //return current frame time
    uint64_t model_animation_instance_writelock::getCurrentFrameTime( void )
    {
        return this->t->getCurrentFrameTime();
    }

};
