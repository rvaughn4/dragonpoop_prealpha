
#include "model_triangle_vertex_instance_readlock.h"
#include "model_triangle_vertex_instance.h"

namespace dragonpoop
{

    //ctor
    model_triangle_vertex_instance_readlock::model_triangle_vertex_instance_readlock( model_triangle_vertex_instance *t, dpmutex_readlock *l ) : model_component_readlock( t, l )
    {
        this->t = t;
    }

    //dtor
    model_triangle_vertex_instance_readlock::~model_triangle_vertex_instance_readlock( void )
    {

    }

    //return instance id
    dpid model_triangle_vertex_instance_readlock::getInstanceId( void )
    {
        return this->t->getInstanceId();
    }
    
};
