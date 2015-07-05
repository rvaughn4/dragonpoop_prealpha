
#include "model_triangle_instance_writelock.h"
#include "model_triangle_instance.h"

namespace dragonpoop
{

    //ctor
    model_triangle_instance_writelock::model_triangle_instance_writelock( model_triangle_instance *t, dpmutex_writelock *l ) : model_component_writelock( t, l )
    {
        this->t = t;
    }

    //dtor
    model_triangle_instance_writelock::~model_triangle_instance_writelock( void )
    {

    }

    //return instance id
    dpid model_triangle_instance_writelock::getInstanceId( void )
    {
        return this->t->getInstanceId();
    }

    //return triangle id
    dpid model_triangle_instance_writelock::getTriangleId( void )
    {
        return this->t->getTriangleId();
    }
    
};
