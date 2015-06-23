
#include "model_animation_frame_readlock.h"
#include "model_animation_frame.h"

namespace dragonpoop
{

    //ctor
    model_animation_frame_readlock::model_animation_frame_readlock( model_animation_frame *t, dpmutex_readlock *l ) : model_component_readlock( t, l )
    {
        this->t = t;
    }

    //dtor
    model_animation_frame_readlock::~model_animation_frame_readlock( void )
    {

    }

    //returns animation id
    dpid model_animation_frame_readlock::getAnimationId( void )
    {
        return this->t->getAnimationId();
    }

    //returns animation
    model_animation_ref *model_animation_frame_readlock::getAnimation( void )
    {
        return this->t->getAnimation();
    }

    //returns frame id
    dpid model_animation_frame_readlock::getFrameId( void )
    {
        return this->t->getFrameId();
    }

    //returns frame
    model_frame_ref *model_animation_frame_readlock::getFrame( void )
    {
        return this->t->getFrame();
    }

    //returns time
    float model_animation_frame_readlock::getTime( void )
    {
        return this->t->getTime();
    }

};
