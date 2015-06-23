
#ifndef dragonpoop_model_frame_joint_writelock_h
#define dragonpoop_model_frame_joint_writelock_h

#include "../model_component/model_component_writelock.h"
#include "../../dpvertex/dpvertexes.h"

namespace dragonpoop
{
    class model_frame_joint;
    class model_frame_joint_ref;
    class model_joint_ref;
    class model_frame_ref;

    class model_frame_joint_writelock : public model_component_writelock
    {

    private:

        model_frame_joint *t;

    protected:

        //ctor
        model_frame_joint_writelock( model_frame_joint *t, dpmutex_writelock *l );
        //dtor
        virtual ~model_frame_joint_writelock( void );

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
        //set position
        void setPosition( dpxyzw *p );
        //set roatation
        void setRotation( dpxyzw *p );

        friend class model_frame_joint;
    };
    
};

#endif