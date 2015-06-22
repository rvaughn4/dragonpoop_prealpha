
#ifndef dragonpoop_model_animation_writelock_h
#define dragonpoop_model_animation_writelock_h

#include "../model_component/model_component_writelock.h"
#include <string>

namespace dragonpoop
{
    class model_animation;
    class model_animation_ref;

    class model_animation_writelock : public model_component_writelock
    {

    private:

        model_animation *t;

    protected:

        //ctor
        model_animation_writelock( model_animation *t, dpmutex_writelock *l );
        //dtor
        virtual ~model_animation_writelock( void );

    public:

        //get name
        void getName( std::string *s );
        //set name
        void setName( std::string *s );
        //get speed
        float getSpeed( void );
        //set speed
        void setSpeed( float s );
        //returns true if autoplay
        bool isAutoPlay( void );
        //sets autoplay mode
        void setAutoPlay( bool b );
        //returns true if repeats
        bool isRepeated( void );
        //set repeat mode
        void setRepeated( bool b );
        //returns time between last frame and first frame when repeated
        unsigned int getRepeatDelay( void );
        //sets repeat delay in ms
        void setRepeatDelay( unsigned int ms );

        friend class model_animation;
    };
    
};

#endif