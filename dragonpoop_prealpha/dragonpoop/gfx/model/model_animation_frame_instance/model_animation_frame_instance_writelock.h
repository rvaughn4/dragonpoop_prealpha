
#ifndef dragonpoop_model_animation_frame_instance_writelock_h
#define dragonpoop_model_animation_frame_instance_writelock_h

#include "../model_component/model_component_writelock.h"

namespace dragonpoop
{

    class model_animation_frame_instance;
    class model_animation_frame_instance_ref;

    class model_animation_frame_instance_writelock : public model_component_writelock
    {

    private:

        model_animation_frame_instance *t;

    protected:

        //ctor
        model_animation_frame_instance_writelock( model_animation_frame_instance *t, dpmutex_writelock *l );
        //dtor
        virtual ~model_animation_frame_instance_writelock( void );

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