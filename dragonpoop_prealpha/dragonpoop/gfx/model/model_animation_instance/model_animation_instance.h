
#ifndef dragonpoop_model_animation_instance_h
#define dragonpoop_model_animation_instance_h

#include "../model_component/model_component_type.h"
#include "../model_component/model_component.h"

namespace dragonpoop
{

    class model_animation_instance_ref;
    class model_animation_instance_readlock;
    class model_animation_instance_writelock;
    class model_animation_frame_instance_ref;

    class model_animation_instance : public model_component
    {

    private:

        dpid instance_id, animation_id;
        uint64_t t_start, t_max, t_delay;
        float speed;
        bool bIsPlaying, bIsRepeat;
        struct
        {
            dpid anim_frame_id, frame_id;
            uint64_t time;
        } current_frame;

        //find last frame time
        void findMaxTime( model_writelock *ml );
        //get props from animation
        void findProps( model_writelock *ml );
        //find current frame
        void findCurrentFrame( dpthread_lock *thd, model_writelock *ml );

    protected:

        //generate read lock
        virtual shared_obj_readlock *genReadLock( shared_obj *p, dpmutex_readlock *l );
        //generate write lock
        virtual shared_obj_writelock *genWriteLock( shared_obj *p, dpmutex_writelock *l );
        //generate ref
        virtual shared_obj_ref *genRef( shared_obj *p, std::shared_ptr<shared_obj_refkernal> *k );
        //do background processing
        virtual void onRun( dpthread_lock *thd, gfx_writelock *g, model_writelock *m, model_component_writelock *l );
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

    public:

        //ctor
        model_animation_instance( dpthread_lock *thd, model_writelock *ml, dpid id, dpid instance_id, dpid animation_id );
        //dtor
        virtual ~model_animation_instance( void );

        friend class model_animation_instance_readlock;
        friend class model_animation_instance_writelock;
    };
    
};

#endif
