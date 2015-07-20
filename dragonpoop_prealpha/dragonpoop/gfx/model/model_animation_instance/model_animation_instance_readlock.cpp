
#include "model_animation_instance_readlock.h"
#include "model_animation_instance.h"

namespace dragonpoop
{

    //ctor
    model_animation_instance_readlock::model_animation_instance_readlock( model_animation_instance *t, dpmutex_readlock *l ) : model_component_readlock( t, l )
    {
        this->t = t;
    }

    //dtor
    model_animation_instance_readlock::~model_animation_instance_readlock( void )
    {

    }

    //return instance id
    dpid model_animation_instance_readlock::getInstanceId( void )
    {
        return this->t->getInstanceId();
    }

    //return animation id
    dpid model_animation_instance_readlock::getAnimationId( void )
    {
        return this->t->getAnimationId();
    }

    //return current frame
    dpid model_animation_instance_readlock::getCurrentFrameId( void )
    {
        return this->t->getCurrentFrameId();
    }

    //return current frame time
    uint64_t model_animation_instance_readlock::getCurrentFrameTime( void )
    {
        return this->t->getCurrentFrameTime();
    }

};
