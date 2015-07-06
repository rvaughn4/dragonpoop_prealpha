
#include "model_group_instance_writelock.h"
#include "model_group_instance.h"

namespace dragonpoop
{

    //ctor
    model_group_instance_writelock::model_group_instance_writelock( model_group_instance *t, dpmutex_writelock *l ) : model_component_writelock( t, l )
    {
        this->t = t;
    }

    //dtor
    model_group_instance_writelock::~model_group_instance_writelock( void )
    {

    }

    //return instance id
    dpid model_group_instance_writelock::getInstanceId( void )
    {
        return this->t->getInstanceId();
    }

    //return group id
    dpid model_group_instance_writelock::getGroupId( void )
    {
        return this->t->getGroupId();
    }

    //return partent id
    dpid model_group_instance_writelock::getParentId( void )
    {
        return this->t->getParentId();
    }

};
