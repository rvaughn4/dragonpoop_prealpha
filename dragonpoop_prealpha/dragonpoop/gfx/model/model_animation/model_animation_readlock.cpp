
#include "model_animation_readlock.h"
#include "model_animation.h"

namespace dragonpoop
{

    //ctor
    model_animation_readlock::model_animation_readlock( model_animation *t, dpmutex_readlock *l ) : model_component_readlock( t, l )
    {
        this->t = t;
    }

    //dtor
    model_animation_readlock::~model_animation_readlock( void )
    {

    }

    //get name
    void model_animation_readlock::getName( std::string *s )
    {
        this->t->getName( s );
    }

    //get speed
    float model_animation_readlock::getSpeed( void )
    {
        return this->t->getSpeed();
    }

    //returns true if autoplay
    bool model_animation_readlock::isAutoPlay( void )
    {
        return this->t->isAutoPlay();
    }

    //returns true if repeats
    bool model_animation_readlock::isRepeated( void )
    {
        return this->t->isRepeated();
    }

    //returns time between last frame and first frame when repeated
    unsigned int model_animation_readlock::getRepeatDelay( void )
    {
        return this->t->getRepeatDelay();
    }

};
