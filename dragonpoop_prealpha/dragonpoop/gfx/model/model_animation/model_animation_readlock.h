
#ifndef dragonpoop_model_animation_readlock_h
#define dragonpoop_model_animation_readlock_h

#include "../model_component/model_component_readlock.h"
#include <string>

namespace dragonpoop
{
    class model_animation;
    class model_animation_ref;

    class model_animation_readlock : public model_component_readlock
    {

    private:

        model_animation *t;

    protected:

        //ctor
        model_animation_readlock( model_animation *t, dpmutex_readlock *l );
        //dtor
        virtual ~model_animation_readlock( void );

    public:

        //get name
        void getName( std::string *s );
        //get speed
        float getSpeed( void );
        //returns true if autoplay
        bool isAutoPlay( void );
        //returns true if repeats
        bool isRepeated( void );
        //returns time between last frame and first frame when repeated
        unsigned int getRepeatDelay( void );

        friend class model_animation;
    };
    
};

#endif