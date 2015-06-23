
#include "model_animation_frame_writelock.h"
#include "model_animation_frame.h"

namespace dragonpoop
{

    //ctor
    model_animation_frame_writelock::model_animation_frame_writelock( model_animation_frame *t, dpmutex_writelock *l ) : model_component_writelock( t, l )
    {
        this->t = t;
    }

    //dtor
    model_animation_frame_writelock::~model_animation_frame_writelock( void )
    {

    }

    //returns animation id
    dpid model_animation_frame_writelock::getAnimationId( void )
    {
        return this->t->getAnimationId();
    }

    //returns animation
    model_animation_ref *model_animation_frame_writelock::getAnimation( void )
    {
        return this->t->getAnimation();
    }

    //returns frame id
    dpid model_animation_frame_writelock::getFrameId( void )
    {
        return this->t->getFrameId();
    }

    //returns frame
    model_frame_ref *model_animation_frame_writelock::getFrame( void )
    {
        return this->t->getFrame();
    }

    //returns time
    float model_animation_frame_writelock::getTime( void )
    {
        return this->t->getTime();
    }

    //sets time
    void model_animation_frame_writelock::setTime( float f )
    {
        this->t->setTime( f );
    }

};
