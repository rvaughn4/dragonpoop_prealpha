
#include "model_animation.h"
#include "model_animation_ref.h"
#include "model_animation_readlock.h"
#include "model_animation_writelock.h"

namespace dragonpoop
{

    //ctor
    model_animation::model_animation( model_writelock *ml, dpid id ) : model_component( ml, id, model_component_type_animation, 0 )
    {
        this->speed = 30.0f;
        this->bIsAutoPlay = 0;
        this->bIsRepeat = 0;
        this->repeat_delay_ms = 100;
    }

    //dtor
    model_animation::~model_animation( void )
    {
        model_component_writelock *l;
        shared_obj_guard g;

        l = (model_component_writelock *)g.writeLock( this );
        g.unlock();
    }

    //generate read lock
    shared_obj_readlock *model_animation::genReadLock( shared_obj *p, dpmutex_readlock *l )
    {
        return new model_animation_readlock( (model_animation *)p, l );
    }

    //generate write lock
    shared_obj_writelock *model_animation::genWriteLock( shared_obj *p, dpmutex_writelock *l )
    {
        return new model_animation_writelock( (model_animation *)p, l );
    }

    //generate ref
    shared_obj_ref *model_animation::genRef( shared_obj *p, std::shared_ptr<shared_obj_refkernal> *k )
    {
        return new model_animation_ref( (model_animation *)p, k );
    }

    //do background processing
    void model_animation::onRun( dpthread_lock *thd, gfx_writelock *g, model_writelock *m, model_component_writelock *l )
    {

    }

    //get name
    void model_animation::getName( std::string *s )
    {
        *s = this->sname;
    }

    //set name
    void model_animation::setName( std::string *s )
    {
        this->sname = *s;
    }

    //get speed
    float model_animation::getSpeed( void )
    {
        return this->speed;
    }

    //set speed
    void model_animation::setSpeed( float s )
    {
        this->speed = s;
    }

    //returns true if autoplay
    bool model_animation::isAutoPlay( void )
    {
        return this->bIsAutoPlay;
    }

    //sets autoplay mode
    void model_animation::setAutoPlay( bool b )
    {
        this->bIsAutoPlay = b;
    }

    //returns true if repeats
    bool model_animation::isRepeated( void )
    {
        return this->bIsRepeat;
    }

    //set repeat mode
    void model_animation::setRepeated( bool b )
    {
        this->bIsRepeat = b;
    }

    //returns time between last frame and first frame when repeated
    unsigned int model_animation::getRepeatDelay( void )
    {
        return this->repeat_delay_ms;
    }

    //sets repeat delay in ms
    void model_animation::setRepeatDelay( unsigned int ms )
    {
        this->repeat_delay_ms = ms;
    }

};
