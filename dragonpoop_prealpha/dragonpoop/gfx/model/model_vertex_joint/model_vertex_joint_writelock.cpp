
#include "model_vertex_joint_writelock.h"
#include "model_vertex_joint.h"

namespace dragonpoop
{

    //ctor
    model_vertex_joint_writelock::model_vertex_joint_writelock( model_vertex_joint *t, dpmutex_writelock *l ) : model_component_writelock( t, l )
    {
        this->t = t;
    }

    //dtor
    model_vertex_joint_writelock::~model_vertex_joint_writelock( void )
    {

    }

    //returns animation id
    dpid model_vertex_joint_writelock::getJointId( void )
    {
        return this->t->getJointId();
    }

    //returns animation
    model_joint_ref *model_vertex_joint_writelock::getJoint( void )
    {
        return this->t->getJoint();
    }

    //returns vertex id
    dpid model_vertex_joint_writelock::getVertexId( void )
    {
        return this->t->getVertexId();
    }

    //returns vertex
    model_vertex_ref *model_vertex_joint_writelock::getVertex( void )
    {
        return this->t->getVertex();
    }

    //returns weight
    float model_vertex_joint_writelock::getWeight( void )
    {
        return this->t->getWeight();
    }

    //sets weight
    void model_vertex_joint_writelock::setWeight( float w )
    {
        this->t->setWeight( w );
    }

};
