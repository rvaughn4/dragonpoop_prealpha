
#include "model_triangle_vertex_instance_writelock.h"
#include "model_triangle_vertex_instance.h"

namespace dragonpoop
{

    //ctor
    model_triangle_vertex_instance_writelock::model_triangle_vertex_instance_writelock( model_triangle_vertex_instance *t, dpmutex_writelock *l ) : model_component_writelock( t, l )
    {
        this->t = t;
    }

    //dtor
    model_triangle_vertex_instance_writelock::~model_triangle_vertex_instance_writelock( void )
    {

    }

    //return instance id
    dpid model_triangle_vertex_instance_writelock::getInstanceId( void )
    {
        return this->t->getInstanceId();
    }

    //return triangle id
    dpid model_triangle_vertex_instance_writelock::getTriangleId( void )
    {
        return this->t->getTriangleId();
    }

    //return vertex id
    dpid model_triangle_vertex_instance_writelock::getVertexId( void )
    {
        return this->t->getVertexId();
    }

    //return triangle vertex id
    dpid model_triangle_vertex_instance_writelock::getTriangleVertexId( void )
    {
        return this->t->getTriangleVertexId();
    }

    //get vertexes
    void model_triangle_vertex_instance_writelock::getVertex( dpvertexindex_buffer *b )
    {
        this->t->getVertex( b );
    }

    //sync vertex
    void model_triangle_vertex_instance_writelock::sync( void )
    {
        this->t->sync();
    }

};
