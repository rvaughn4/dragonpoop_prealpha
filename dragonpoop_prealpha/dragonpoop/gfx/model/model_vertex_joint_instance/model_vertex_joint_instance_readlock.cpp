
#include "model_vertex_joint_instance_readlock.h"
#include "model_vertex_joint_instance.h"

namespace dragonpoop
{

    //ctor
    model_vertex_joint_instance_readlock::model_vertex_joint_instance_readlock( model_vertex_joint_instance *t, dpmutex_readlock *l ) : model_component_readlock( t, l )
    {
        this->t = t;
    }

    //dtor
    model_vertex_joint_instance_readlock::~model_vertex_joint_instance_readlock( void )
    {

    }

    //return instance id
    dpid model_vertex_joint_instance_readlock::getInstanceId( void )
    {
        return this->t->getInstanceId();
    }

    //return vertex_joint id
    dpid model_vertex_joint_instance_readlock::getVertexJointId( void )
    {
        return this->t->getVertexJointId();
    }

    //return joint id
    dpid model_vertex_joint_instance_readlock::getJointId( void )
    {
        return this->t->getJointId();
    }

    //return frame id
    dpid model_vertex_joint_instance_readlock::getVertexId( void )
    {
        return this->t->getVertexId();
    }
    
};
