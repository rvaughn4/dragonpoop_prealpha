
#ifndef dragonpoop_model_animation_h
#define dragonpoop_model_animation_h

#include "../model_component/model_component_type.h"
#include "../model_component/model_component.h"
#include <string>

namespace dragonpoop
{

    class model_animation_ref;
    class model_animation_readlock;
    class model_animation_writelock;

    class model_animation : public model_component
    {

    private:

        std::string sname;
        float speed;
        bool bIsAutoPlay, bIsRepeat;
        unsigned int repeat_delay_ms;

    protected:

        //generate read lock
        virtual shared_obj_readlock *genReadLock( shared_obj *p, dpmutex_readlock *l );
        //generate write lock
        virtual shared_obj_writelock *genWriteLock( shared_obj *p, dpmutex_writelock *l );
        //generate ref
        virtual shared_obj_ref *genRef( shared_obj *p, std::shared_ptr<shared_obj_refkernal> *k );
        //do background processing
        virtual void onRun( dpthread_lock *thd, gfx_writelock *g, model_writelock *m, model_component_writelock *l );
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

    public:

        //ctor
        model_animation( model_writelock *ml, dpid id );
        //dtor
        virtual ~model_animation( void );

        friend class model_animation_readlock;
        friend class model_animation_writelock;
    };
    
};

#endif
