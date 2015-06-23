
#include "model_frame_joint_writelock.h"
#include "model_frame_joint.h"

namespace dragonpoop
{

    //ctor
    model_frame_joint_writelock::model_frame_joint_writelock( model_frame_joint *t, dpmutex_writelock *l ) : model_component_writelock( t, l )
    {
        this->t = t;
    }

    //dtor
    model_frame_joint_writelock::~model_frame_joint_writelock( void )
    {

    }

    //returns animation id
    dpid model_frame_joint_writelock::getJointId( void )
    {
        return this->t->getJointId();
    }

    //returns animation
    model_joint_ref *model_frame_joint_writelock::getJoint( void )
    {
        return this->t->getJoint();
    }

    //returns frame id
    dpid model_frame_joint_writelock::getFrameId( void )
    {
        return this->t->getFrameId();
    }

    //returns frame
    model_frame_ref *model_frame_joint_writelock::getFrame( void )
    {
        return this->t->getFrame();
    }

    //get position
    void model_frame_joint_writelock::getPosition( dpxyzw *p )
    {
        this->t->getPosition( p );
    }

    //get roatation
    void model_frame_joint_writelock::getRotation( dpxyzw *p )
    {
        this->t->getRotation( p );
    }

    //set position
    void model_frame_joint_writelock::setPosition( dpxyzw *p )
    {
        this->t->setPosition( p );
    }

    //set roatation
    void model_frame_joint_writelock::setRotation( dpxyzw *p )
    {
        this->t->setRotation( p );
    }

};
