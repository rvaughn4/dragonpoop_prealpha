
#ifndef dragonpoop_model_frame_joint_readlock_h
#define dragonpoop_model_frame_joint_readlock_h

#include "../model_component/model_component_readlock.h"
#include "../../dpvertex/dpvertexes.h"

namespace dragonpoop
{
    class model_frame_joint;
    class model_frame_joint_ref;
    class model_joint_ref;
    class model_frame_ref;

    class model_frame_joint_readlock : public model_component_readlock
    {

    private:

        model_frame_joint *t;

    protected:

        //ctor
        model_frame_joint_readlock( model_frame_joint *t, dpmutex_readlock *l );
        //dtor
        virtual ~model_frame_joint_readlock( void );

    public:

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

        friend class model_frame_joint;
    };
    
};

#endif