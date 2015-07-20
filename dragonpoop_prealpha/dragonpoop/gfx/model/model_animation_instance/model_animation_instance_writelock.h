
#ifndef dragonpoop_model_animation_instance_writelock_h
#define dragonpoop_model_animation_instance_writelock_h

#include "../model_component/model_component_writelock.h"

namespace dragonpoop
{

    class model_animation_instance;
    class model_animation_instance_ref;
    class dpthread_lock;

    class model_animation_instance_writelock : public model_component_writelock
    {

    private:

        model_animation_instance *t;

    protected:

        //ctor
        model_animation_instance_writelock( model_animation_instance *t, dpmutex_writelock *l );
        //dtor
        virtual ~model_animation_instance_writelock( void );

    public:

        //return instance id
        dpid getInstanceId( void );
        //return animation id
        dpid getAnimationId( void );
        //sync animation
        void sync( dpthread_lock *thd, model_writelock *ml );
        //return current frame
        dpid getCurrentFrameId( void );
        //return current frame time
        uint64_t getCurrentFrameTime( void );

        friend class model_animation_instance;
    };
    
};

#endif