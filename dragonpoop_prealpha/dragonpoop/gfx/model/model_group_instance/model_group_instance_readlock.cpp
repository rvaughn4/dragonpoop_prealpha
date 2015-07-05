
#include "model_group_instance_readlock.h"
#include "model_group_instance.h"

namespace dragonpoop
{

    //ctor
    model_group_instance_readlock::model_group_instance_readlock( model_group_instance *t, dpmutex_readlock *l ) : model_component_readlock( t, l )
    {
        this->t = t;
    }

    //dtor
    model_group_instance_readlock::~model_group_instance_readlock( void )
    {

    }

    //return instance id
    dpid model_group_instance_readlock::getInstanceId( void )
    {
        return this->t->getInstanceId();
    }

    //return group id
    dpid model_group_instance_readlock::getGroupId( void )
    {
        return this->t->getGroupId();
    }
    
};
