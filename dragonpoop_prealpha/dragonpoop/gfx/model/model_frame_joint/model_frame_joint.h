
#ifndef dragonpoop_model_frame_joint_h
#define dragonpoop_model_frame_joint_h

#include "../model_component/model_component_type.h"
#include "../model_component/model_component.h"
#include "../../dpvertex/dpvertexes.h"

namespace dragonpoop
{

    class model_frame_joint_ref;
    class model_frame_joint_readlock;
    class model_frame_joint_writelock;
    class model_joint_ref;
    class model_frame_ref;

    class model_frame_joint : public model_component
    {

    private:

        dpid joint_id, frame_id;
        dpxyzw pos, rot;

    protected:

        //generate read lock
        virtual shared_obj_readlock *genReadLock( shared_obj *p, dpmutex_readlock *l );
        //generate write lock
        virtual shared_obj_writelock *genWriteLock( shared_obj *p, dpmutex_writelock *l );
        //generate ref
        virtual shared_obj_ref *genRef( shared_obj *p, std::shared_ptr<shared_obj_refkernal> *k );
        //do background processing
        virtual void onRun( dpthread_lock *thd, gfx_writelock *g, model_writelock *m, model_component_writelock *l );
        //returns joint id
        dpid getJointId( void );
        //returns joint
        model_joint_ref *getJoint( void );
        //returns frame id
        dpid getFrameId( void );
        //returns frame
        model_frame_ref *getFrame( void );
        //get position
        void getPosition( dpxyzw *p );
        //get roatation
        void getRotation( dpxyzw *p );
        //set position
        void setPosition( dpxyzw *p );
        //set roatation
        void setRotation( dpxyzw *p );

    public:

        //ctor
        model_frame_joint( model_writelock *ml, dpid id, dpid frame_id, dpid joint_id );
        //dtor
        virtual ~model_frame_joint( void );

        friend class model_frame_joint_readlock;
        friend class model_frame_joint_writelock;
    };
    
};

#endif
