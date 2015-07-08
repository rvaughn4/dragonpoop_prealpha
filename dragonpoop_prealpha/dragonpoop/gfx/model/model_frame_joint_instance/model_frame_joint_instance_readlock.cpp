
#include "model_frame_joint_instance_readlock.h"
#include "model_frame_joint_instance.h"

namespace dragonpoop
{

    //ctor
    model_frame_joint_instance_readlock::model_frame_joint_instance_readlock( model_frame_joint_instance *t, dpmutex_readlock *l ) : model_component_readlock( t, l )
    {
        this->t = t;
    }

    //dtor
    model_frame_joint_instance_readlock::~model_frame_joint_instance_readlock( void )
    {

    }

    //return instance id
    dpid model_frame_joint_instance_readlock::getInstanceId( void )
    {
        return this->t->getInstanceId();
    }

    //return frame_joint id
    dpid model_frame_joint_instance_readlock::getFrameJointId( void )
    {
        return this->t->getFrameJointId();
    }

    //return joint id
    dpid model_frame_joint_instance_readlock::getJointId( void )
    {
        return this->t->getJointId();
    }

    //return frame id
    dpid model_frame_joint_instance_readlock::getFrameId( void )
    {
        return this->t->getFrameId();
    }
    
};
