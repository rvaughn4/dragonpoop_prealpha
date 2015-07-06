
#ifndef dragonpoop_model_animation_frame_instance_readlock_h
#define dragonpoop_model_animation_frame_instance_readlock_h

#include "../model_component/model_component_readlock.h"

namespace dragonpoop
{

    class model_animation_frame_instance;
    class model_animation_frame_instance_ref;

    class model_animation_frame_instance_readlock : public model_component_readlock
    {

    private:

        model_animation_frame_instance *t;

    protected:

        //ctor
        model_animation_frame_instance_readlock( model_animation_frame_instance *t, dpmutex_readlock *l );
        //dtor
        virtual ~model_animation_frame_instance_readlock( void );

    public:

        //return instance id
        dpid getInstanceId( void );
        //return animation_frame id
        dpid getAnimationFrameId( void );
        //return animation id
        dpid getAnimationId( void );
        //return frame id
        dpid getFrameId( void );

        friend class model_animation_frame_instance;
    };
    
};

#endif