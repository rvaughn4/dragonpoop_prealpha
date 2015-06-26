
#include "model_vertex_joint_readlock.h"
#include "model_vertex_joint.h"

namespace dragonpoop
{

    //ctor
    model_vertex_joint_readlock::model_vertex_joint_readlock( model_vertex_joint *t, dpmutex_readlock *l ) : model_component_readlock( t, l )
    {
        this->t = t;
    }

    //dtor
    model_vertex_joint_readlock::~model_vertex_joint_readlock( void )
    {

    }

    //returns animation id
    dpid model_vertex_joint_readlock::getJointId( void )
    {
        return this->t->getJointId();
    }

    //returns animation
    model_joint_ref *model_vertex_joint_readlock::getJoint( void )
    {
        return this->t->getJoint();
    }

    //returns vertex id
    dpid model_vertex_joint_readlock::getVertexId( void )
    {
        return this->t->getVertexId();
    }

    //returns vertex
    model_vertex_ref *model_vertex_joint_readlock::getVertex( void )
    {
        return this->t->getVertex();
    }

    //returns weight
    float model_vertex_joint_readlock::getWeight( void )
    {
        return this->t->getWeight();
    }

};
