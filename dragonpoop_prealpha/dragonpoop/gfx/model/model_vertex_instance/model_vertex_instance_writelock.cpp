
#include "model_vertex_instance_writelock.h"
#include "model_vertex_instance.h"

namespace dragonpoop
{

    //ctor
    model_vertex_instance_writelock::model_vertex_instance_writelock( model_vertex_instance *t, dpmutex_writelock *l ) : model_component_writelock( t, l )
    {
        this->t = t;
    }

    //dtor
    model_vertex_instance_writelock::~model_vertex_instance_writelock( void )
    {

    }

    //return instance id
    dpid model_vertex_instance_writelock::getInstanceId( void )
    {
        return this->t->getInstanceId();
    }

    //return vertex id
    dpid model_vertex_instance_writelock::getVertexId( void )
    {
        return this->t->getVertexId();
    }

    //get vertex data
    void model_vertex_instance_writelock::getVertex( dpvertex *v )
    {
        this->t->getVertex( v );
    }

    //sync vertex
    void model_vertex_instance_writelock::sync( void )
    {
        this->t->sync();
    }

};
