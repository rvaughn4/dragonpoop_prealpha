
#include "model_animation_frame_instance_readlock.h"
#include "model_animation_frame_instance.h"

namespace dragonpoop
{

    //ctor
    model_animation_frame_instance_readlock::model_animation_frame_instance_readlock( model_animation_frame_instance *t, dpmutex_readlock *l ) : model_component_readlock( t, l )
    {
        this->t = t;
    }

    //dtor
    model_animation_frame_instance_readlock::~model_animation_frame_instance_readlock( void )
    {

    }

    //return instance id
    dpid model_animation_frame_instance_readlock::getInstanceId( void )
    {
        return this->t->getInstanceId();
    }

    //return animation_frame id
    dpid model_animation_frame_instance_readlock::getAnimationFrameId( void )
    {
        return this->t->getAnimationFrameId();
    }

    //return animation id
    dpid model_animation_frame_instance_readlock::getAnimationId( void )
    {
        return this->t->getAnimationId();
    }

    //return frame id
    dpid model_animation_frame_instance_readlock::getFrameId( void )
    {
        return this->t->getFrameId();
    }

};
