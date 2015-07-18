
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

    //return triangle id
    dpid model_triangle_vertex_instance_readlock::getTriangleId( void )
    {
        return this->t->getTriangleId();
    }

    //return vertex id
    dpid model_triangle_vertex_instance_readlock::getVertexId( void )
    {
        return this->t->getVertexId();
    }

    //return triangle vertex id
    dpid model_triangle_vertex_instance_readlock::getTriangleVertexId( void )
    {
        return this->t->getTriangleVertexId();
    }

    //get vertexes
    void model_triangle_vertex_instance_readlock::getVertex( dpvertexindex_buffer *b )
    {
        this->t->getVertex( b );
    }

};
