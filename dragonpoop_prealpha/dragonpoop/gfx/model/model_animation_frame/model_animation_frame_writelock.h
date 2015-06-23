
#ifndef dragonpoop_model_animation_frame_writelock_h
#define dragonpoop_model_animation_frame_writelock_h

#include "../model_component/model_component_writelock.h"
#include <string>

namespace dragonpoop
{
    class model_animation_frame;
    class model_animation_frame_ref;
    class model_animation_ref;
    class model_frame_ref;

    class model_animation_frame_writelock : public model_component_writelock
    {

    private:

        model_animation_frame *t;

    protected:

        //ctor
        model_animation_frame_writelock( model_animation_frame *t, dpmutex_writelock *l );
        //dtor
        virtual ~model_animation_frame_writelock( void );

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
        //sets time
        void setTime( float f );

        friend class model_animation_frame;
    };
    
};

#endif