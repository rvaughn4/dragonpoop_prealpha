
#include "model_vertex_joint_instance_writelock.h"
#include "model_vertex_joint_instance.h"

namespace dragonpoop
{

    //ctor
    model_vertex_joint_instance_writelock::model_vertex_joint_instance_writelock( model_vertex_joint_instance *t, dpmutex_writelock *l ) : model_component_writelock( t, l )
    {
        this->t = t;
    }

    //dtor
    model_vertex_joint_instance_writelock::~model_vertex_joint_instance_writelock( void )
    {

    }

    //return instance id
    dpid model_vertex_joint_instance_writelock::getInstanceId( void )
    {
        return this->t->getInstanceId();
    }

    //return vertex_joint id
    dpid model_vertex_joint_instance_writelock::getVertexJointId( void )
    {
        return this->t->getVertexJointId();
    }

    //return joint id
    dpid model_vertex_joint_instance_writelock::getJointId( void )
    {
        return this->t->getJointId();
    }

    //return vertex id
    dpid model_vertex_joint_instance_writelock::getVertexId( void )
    {
        return this->t->getVertexId();
    }
    
};
