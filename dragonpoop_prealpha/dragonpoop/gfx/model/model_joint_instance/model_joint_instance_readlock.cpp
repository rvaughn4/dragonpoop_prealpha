
#include "model_joint_instance_readlock.h"
#include "model_joint_instance.h"

namespace dragonpoop
{

    //ctor
    model_joint_instance_readlock::model_joint_instance_readlock( model_joint_instance *t, dpmutex_readlock *l ) : model_component_readlock( t, l )
    {
        this->t = t;
    }

    //dtor
    model_joint_instance_readlock::~model_joint_instance_readlock( void )
    {

    }

    //return instance id
    dpid model_joint_instance_readlock::getInstanceId( void )
    {
        return this->t->getInstanceId();
    }

    //return joint id
    dpid model_joint_instance_readlock::getJointId( void )
    {
        return this->t->getJointId();
    }
    
};