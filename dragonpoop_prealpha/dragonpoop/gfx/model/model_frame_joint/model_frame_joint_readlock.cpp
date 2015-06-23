
#include "model_frame_joint_readlock.h"
#include "model_frame_joint.h"

namespace dragonpoop
{

    //ctor
    model_frame_joint_readlock::model_frame_joint_readlock( model_frame_joint *t, dpmutex_readlock *l ) : model_component_readlock( t, l )
    {
        this->t = t;
    }

    //dtor
    model_frame_joint_readlock::~model_frame_joint_readlock( void )
    {

    }

    //returns animation id
    dpid model_frame_joint_readlock::getJointId( void )
    {
        return this->t->getJointId();
    }

    //returns animation
    model_joint_ref *model_frame_joint_readlock::getJoint( void )
    {
        return this->t->getJoint();
    }

    //returns frame id
    dpid model_frame_joint_readlock::getFrameId( void )
    {
        return this->t->getFrameId();
    }

    //returns frame
    model_frame_ref *model_frame_joint_readlock::getFrame( void )
    {
        return this->t->getFrame();
    }

    //get position
    void model_frame_joint_readlock::getPosition( dpxyzw *p )
    {
        this->t->getPosition( p );
    }

    //get roatation
    void model_frame_joint_readlock::getRotation( dpxyzw *p )
    {
        this->t->getRotation( p );
    }

};
