
#include "model_animation_instance.h"
#include "model_animation_instance_readlock.h"
#include "model_animation_instance_writelock.h"
#include "model_animation_instance_ref.h"
#include "../model_animation/model_animation_readlock.h"
#include "../model_animation/model_animation_ref.h"
#include "../model_animation_frame/model_animation_frame_readlock.h"
#include "../model_animation_frame/model_animation_frame_ref.h"
#include "../model_writelock.h"
#include "../../../core/dpthread/dpthread_lock.h"
#include <iostream>

namespace dragonpoop
{

    //ctor
    model_animation_instance::model_animation_instance( dpthread_lock *thd, model_writelock *ml, dpid id, dpid instance_id, dpid animation_id ) : model_component( ml, id,model_component_type_animation_instance, 0 )
    {
        this->instance_id = instance_id;
        this->animation_id = animation_id;
        memset( &this->current_frame, 0, sizeof( this->current_frame ) );
        this->t_start = thd->getTicks();
        this->findProps( ml );
        this->findMaxTime( ml );
        this->sync( thd, ml );
    }

    //dtor
    model_animation_instance::~model_animation_instance( void )
    {

    }

    //generate read lock
    shared_obj_readlock *model_animation_instance::genReadLock( shared_obj *p, dpmutex_readlock *l )
    {
        return new model_animation_instance_readlock( (model_animation_instance *)p, l );
    }

    //generate write lock
    shared_obj_writelock *model_animation_instance::genWriteLock( shared_obj *p, dpmutex_writelock *l )
    {
        return new model_animation_instance_writelock( (model_animation_instance *)p, l );
    }

    //generate ref
    shared_obj_ref *model_animation_instance::genRef( shared_obj *p, std::shared_ptr<shared_obj_refkernal> *k )
    {
        return new model_animation_instance_ref( (model_animation_instance *)p, k );
    }

    //do background processing
    void model_animation_instance::onRun( dpthread_lock *thd, gfx_writelock *g, model_writelock *m, model_component_writelock *l )
    {

    }

    //return instance id
    dpid model_animation_instance::getInstanceId( void )
    {
        return this->instance_id;
    }

    //return vertex id
    dpid model_animation_instance::getAnimationId( void )
    {
        return this->animation_id;
    }

    //find last frame time
    void model_animation_instance::findMaxTime( model_writelock *ml )
    {
        std::list<model_animation_frame_ref *> l;
        std::list<model_animation_frame_ref *>::iterator i;
        model_animation_frame_ref *p;
        model_animation_frame_readlock *pl;
        shared_obj_guard o;
        uint64_t t;

        ml->getAnimationFramesByAnimation( &l, this->animation_id );

        this->t_max = 0;
        for( i = l.begin(); i != l.end(); ++i )
        {
            p = *i;
            pl = (model_animation_frame_readlock *)o.readLock( p );
            if( !pl )
                continue;

            t = pl->getTime();
            if( t > this->t_max )
                this->t_max = t;
        }

        ml->releaseGetAnimationFrames( &l );
    }

    //get props from animation
    void model_animation_instance::findProps( model_writelock *ml )
    {
        model_animation_ref *r;
        model_animation_readlock *rl;
        shared_obj_guard o;

        r = ml->findAnimation( this->animation_id );
        if( !r )
            return;
        rl = (model_animation_readlock *)o.readLock( r );
        delete r;
        if( !rl )
            return;

        this->bIsRepeat = rl->isRepeated();
        this->bIsPlaying = rl->isAutoPlay();
        this->t_delay = rl->getRepeatDelay();
        this->speed = rl->getSpeed();
    }

    //find current frame
    void model_animation_instance::findCurrentFrame( dpthread_lock *thd, model_writelock *ml )
    {
        std::list<model_animation_frame_ref *> l;
        std::list<model_animation_frame_ref *>::iterator i;
        model_animation_frame_ref *p;
        model_animation_frame_readlock *pl;
        shared_obj_guard o;
        uint64_t t, dt, lt;
        float ct;

        t = thd->getTicks();
        if( !this->bIsPlaying )
        {
            memset( &this->current_frame, 0, sizeof( this->current_frame ) );
            this->current_frame.time = t;
        }

        ml->getAnimationFramesByAnimation( &l, this->animation_id );

        dt = t - this->t_start;
        ct = (float)dt / this->speed;
        if( ct >= this->t_max )
        {
            if( !this->bIsRepeat || !this->t_max )
            {
                memset( &this->current_frame, 0, sizeof( this->current_frame ) );
                this->current_frame.time = t;
                this->bIsPlaying = 0;
                return;
            }

            while( ct >= this->t_max )
                ct -= this->t_max;
        }

        this->current_frame.time = t;
        lt = this->t_max + 1;
        for( i = l.begin(); i != l.end(); ++i )
        {
            p = *i;
            pl = (model_animation_frame_readlock *)o.tryReadLock( p, 100 );
            if( !pl )
                continue;

            dt = pl->getTime();
            if( dt < ct )
                continue;
            if( dt >= lt )
                continue;

            lt = dt;
            this->current_frame.frame_id = pl->getFrameId();
            this->current_frame.anim_frame_id = pl->getId();
            this->current_frame.time = this->speed * dt + this->t_start;
        }

        std::cout << "frame: " << lt << "\r\n";
    }

    //sync animation
    void model_animation_instance::sync( dpthread_lock *thd, model_writelock *ml )
    {
        this->findCurrentFrame( thd, ml );
    }

    //return current frame
    dpid model_animation_instance::getCurrentFrameId( void )
    {
        return this->current_frame.frame_id;
    }

    //return current frame time
    uint64_t model_animation_instance::getCurrentFrameTime( void )
    {
        return this->current_frame.time;
    }

};
