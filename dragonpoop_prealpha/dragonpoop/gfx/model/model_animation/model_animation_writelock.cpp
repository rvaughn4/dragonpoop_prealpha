
#include "model_animation_writelock.h"
#include "model_animation.h"

namespace dragonpoop
{

    //ctor
    model_animation_writelock::model_animation_writelock( model_animation *t, dpmutex_writelock *l ) : model_component_writelock( t, l )
    {
        this->t = t;
    }

    //dtor
    model_animation_writelock::~model_animation_writelock( void )
    {

    }

    //get name
    void model_animation_writelock::getName( std::string *s )
    {
        this->t->getName( s );
    }

    //set name
    void model_animation_writelock::setName( std::string *s )
    {
        this->t->setName( s );
    }

    //get speed
    float model_animation_writelock::getSpeed( void )
    {
        return this->t->getSpeed();
    }

    //set speed
    void model_animation_writelock::setSpeed( float s )
    {
        this->t->setSpeed( s );
    }

    //returns true if autoplay
    bool model_animation_writelock::isAutoPlay( void )
    {
        return this->t->isAutoPlay();
    }

    //sets autoplay mode
    void model_animation_writelock::setAutoPlay( bool b )
    {
        this->t->setAutoPlay( b );
    }

    //returns true if repeats
    bool model_animation_writelock::isRepeated( void )
    {
        return this->t->isRepeated();
    }

    //set repeat mode
    void model_animation_writelock::setRepeated( bool b )
    {
        this->t->setRepeated( b );
    }

    //returns time between last frame and first frame when repeated
    unsigned int model_animation_writelock::getRepeatDelay( void )
    {
        return this->t->getRepeatDelay();
    }

    //sets repeat delay in ms
    void model_animation_writelock::setRepeatDelay( unsigned int ms )
    {
        this->t->setRepeatDelay( ms );
    }

};
