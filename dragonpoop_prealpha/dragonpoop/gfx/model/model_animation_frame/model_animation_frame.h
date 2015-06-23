
#ifndef dragonpoop_model_animation_frame_h
#define dragonpoop_model_animation_frame_h

#include "../model_component/model_component_type.h"
#include "../model_component/model_component.h"

namespace dragonpoop
{

    class model_animation_frame_ref;
    class model_animation_frame_readlock;
    class model_animation_frame_writelock;
    class model_animation_ref;
    class model_frame_ref;

    class model_animation_frame : public model_component
    {

    private:

        dpid animation_id, frame_id;
        float time;

    protected:

        //generate read lock
        virtual shared_obj_readlock *genReadLock( shared_obj *p, dpmutex_readlock *l );
        //generate write lock
        virtual shared_obj_writelock *genWriteLock( shared_obj *p, dpmutex_writelock *l );
        //generate ref
        virtual shared_obj_ref *genRef( shared_obj *p, std::shared_ptr<shared_obj_refkernal> *k );
        //do background processing
        virtual void onRun( dpthread_lock *thd, gfx_writelock *g, model_writelock *m, model_component_writelock *l );
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

    public:

        //ctor
        model_animation_frame( model_writelock *ml, dpid id, dpid animation_id, dpid frame_id, float ftime );
        //dtor
        virtual ~model_animation_frame( void );

        friend class model_animation_frame_readlock;
        friend class model_animation_frame_writelock;
    };
    
};

#endif
