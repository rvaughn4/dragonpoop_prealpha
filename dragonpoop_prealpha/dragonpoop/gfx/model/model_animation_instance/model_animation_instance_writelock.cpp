
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

};
