
#include "model_triangle_vertex_readlock.h"
#include "model_triangle_vertex.h"

namespace dragonpoop
{

    //ctor
    model_triangle_vertex_readlock::model_triangle_vertex_readlock( model_triangle_vertex *t, dpmutex_readlock *l ) : model_component_readlock( t, l )
    {
        this->t = t;
    }

    //dtor
    model_triangle_vertex_readlock::~model_triangle_vertex_readlock( void )
    {

    }

    //get triangle id
    dpid model_triangle_vertex_readlock::getTriangleId( void )
    {
        return this->t->getTriangleId();
    }

    //get triangle
    model_triangle_ref *model_triangle_vertex_readlock::getTriangle( void )
    {
        return this->t->getTriangle();
    }

    //get vertex id
    dpid model_triangle_vertex_readlock::getVertexId( void )
    {
        return this->t->getVertexId();
    }

    //get vertex
    model_vertex_ref *model_triangle_vertex_readlock::getVertex( void )
    {
        return this->t->getVertex();
    }

    //get normal
    void model_triangle_vertex_readlock::getNormal( dpxyzw *p )
    {
        this->t->getNormal( p );
    }

    //get normal
    void model_triangle_vertex_readlock::getNormal( dpxyzw_f *p )
    {
        this->t->getNormal( p );
    }

    //get normal
    void model_triangle_vertex_readlock::getNormal( dpxyz_f *p )
    {
        this->t->getNormal( p );
    }

    //get texcoord
    void model_triangle_vertex_readlock::getTexcoord( uint8_t index, dpst *p )
    {
        this->t->getTexcoord( index, p );
    }

    //get texcoord
    void model_triangle_vertex_readlock::getTexcoord( uint8_t index, dpst_f *p )
    {
        this->t->getTexcoord( index, p );
    }

};
