
#include "model_joint_instance_writelock.h"
#include "model_joint_instance.h"

namespace dragonpoop
{

    //ctor
    model_joint_instance_writelock::model_joint_instance_writelock( model_joint_instance *t, dpmutex_writelock *l ) : model_component_writelock( t, l )
    {
        this->t = t;
    }

    //dtor
    model_joint_instance_writelock::~model_joint_instance_writelock( void )
    {

    }

    //return instance id
    dpid model_joint_instance_writelock::getInstanceId( void )
    {
        return this->t->getInstanceId();
    }

    //return joint id
    dpid model_joint_instance_writelock::getJointId( void )
    {
        return this->t->getJointId();
    }

    //sync joint
    void model_joint_instance_writelock::sync( dpthread_lock *thd, model_writelock *ml )
    {
        this->t->sync( thd, ml );
    }

    //get translation for this joint
    void model_joint_instance_writelock::getTranslation( dpxyzw *x )
    {
        this->t->getTranslation( x );
    }

    //get rotation for this joint
    void model_joint_instance_writelock::getRotation( dpxyzw *x )
    {
        this->t->getRotation( x );
    }

    //get animation time for this joint
    uint64_t model_joint_instance_writelock::getTime( void )
    {
        return this->t->getTime();
    }

};
