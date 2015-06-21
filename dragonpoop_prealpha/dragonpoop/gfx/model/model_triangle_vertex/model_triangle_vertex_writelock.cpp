
#include "model_triangle_vertex_writelock.h"
#include "model_triangle_vertex.h"

namespace dragonpoop
{

    //ctor
    model_triangle_vertex_writelock::model_triangle_vertex_writelock( model_triangle_vertex *t, dpmutex_writelock *l ) : model_component_writelock( t, l )
    {
        this->t = t;
    }

    //dtor
    model_triangle_vertex_writelock::~model_triangle_vertex_writelock( void )
    {

    }

    //get triangle id
    dpid model_triangle_vertex_writelock::getTriangleId( void )
    {
        return this->t->getTriangleId();
    }

    //get triangle
    model_triangle_ref *model_triangle_vertex_writelock::getTriangle( void )
    {
        return this->t->getTriangle();
    }

    //get vertex id
    dpid model_triangle_vertex_writelock::getVertexId( void )
    {
        return this->t->getVertexId();
    }

    //get vertex
    model_vertex_ref *model_triangle_vertex_writelock::getVertex( void )
    {
        return this->t->getVertex();
    }

    //set normal
    void model_triangle_vertex_writelock::setNormal( dpxyzw *p )
    {
        this->t->setNormal( p );
    }

    //set normal
    void model_triangle_vertex_writelock::setNormal( dpxyzw_f *p )
    {
        this->t->setNormal( p );
    }

    //set normal
    void model_triangle_vertex_writelock::setNormal( dpxyz_f *p )
    {
        this->t->setNormal( p );
    }

    //get normal
    void model_triangle_vertex_writelock::getNormal( dpxyzw *p )
    {
        this->t->getNormal( p );
    }

    //get normal
    void model_triangle_vertex_writelock::getNormal( dpxyzw_f *p )
    {
        this->t->getNormal( p );
    }

    //get normal
    void model_triangle_vertex_writelock::getNormal( dpxyz_f *p )
    {
        this->t->getNormal( p );
    }

    //set texcoord
    void model_triangle_vertex_writelock::setTexcoord( uint8_t index, dpst *p )
    {
        this->t->setTexcoord( index, p );
    }

    //set texcoord
    void model_triangle_vertex_writelock::setTexcoord( uint8_t index, dpst_f *p )
    {
        this->t->setTexcoord( index, p );
    }

    //get texcoord
    void model_triangle_vertex_writelock::getTexcoord( uint8_t index, dpst *p )
    {
        this->t->getTexcoord( index, p );
    }

    //get texcoord
    void model_triangle_vertex_writelock::getTexcoord( uint8_t index, dpst_f *p )
    {
        this->t->getTexcoord( index, p );

    }

};
