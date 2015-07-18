
#include "model_vertex_instance_readlock.h"
#include "model_vertex_instance.h"

namespace dragonpoop
{

    //ctor
    model_vertex_instance_readlock::model_vertex_instance_readlock( model_vertex_instance *t, dpmutex_readlock *l ) : model_component_readlock( t, l )
    {
        this->t = t;
    }

    //dtor
    model_vertex_instance_readlock::~model_vertex_instance_readlock( void )
    {

    }

    //return instance id
    dpid model_vertex_instance_readlock::getInstanceId( void )
    {
        return this->t->getInstanceId();
    }

    //return vertex id
    dpid model_vertex_instance_readlock::getVertexId( void )
    {
        return this->t->getVertexId();
    }

    //get vertex data
    void model_vertex_instance_readlock::getVertex( model_writelock *ml, dpvertex *v )
    {
        this->t->getVertex( ml, v );
    }

};
