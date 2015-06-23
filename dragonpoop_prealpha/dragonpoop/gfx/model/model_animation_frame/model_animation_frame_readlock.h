
#ifndef dragonpoop_model_animation_frame_readlock_h
#define dragonpoop_model_animation_frame_readlock_h

#include "../model_component/model_component_readlock.h"
#include <string>

namespace dragonpoop
{
    class model_animation_frame;
    class model_animation_frame_ref;
    class model_animation_ref;
    class model_frame_ref;

    class model_animation_frame_readlock : public model_component_readlock
    {

    private:

        model_animation_frame *t;

    protected:

        //ctor
        model_animation_frame_readlock( model_animation_frame *t, dpmutex_readlock *l );
        //dtor
        virtual ~model_animation_frame_readlock( void );

    public:

        //returns animation id
        dpid getAnimationId( void );
        //returns animation
        model_animation_ref *getAnimation( void );
        //returns frame id
        dpid getFrameId( void );
        //returns frame
        model_frame_ref *getFrame( void );
        //returns time
        float getTime( void );

        friend class model_animation_frame;
    };
    
};

#endif