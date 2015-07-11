
#include "model_instance_writelock.h"
#include "model_instance.h"

namespace dragonpoop
{

    //ctor
    model_instance_writelock::model_instance_writelock( model_instance *t, dpmutex_writelock *l ) : model_component_writelock( t, l )
    {
        this->t = t;
    }

    //dtor
    model_instance_writelock::~model_instance_writelock( void )
    {

    }

    //get group instances
    unsigned int model_instance_writelock::getGroups( std::list<model_group_instance_ref *> *l )
    {
        return this->t->getGroups( l );
    }

    //get group instances by parent
    unsigned int model_instance_writelock::getGroupsByParent( dpid parent_id, std::list<model_group_instance_ref *> *l )
    {
        return this->t->getGroupsByParent( parent_id, l );
    }

    //release list returned by getGroups()
    void model_instance_writelock::releaseGetGroups( std::list<model_group_instance_ref *> *l )
    {
        model_instance::releaseGetGroups( l );
    }

    //get triangle instances
    unsigned int model_instance_writelock::getTriangles( std::list<model_triangle_instance_ref *> *l )
    {
        return this->t->getTriangles( l );
    }

    //get triangle instances by group
    unsigned int model_instance_writelock::getTrianglesByGroup( dpid group_id, std::list<model_triangle_instance_ref *> *l )
    {
        return this->t->getTrianglesByGroup( group_id, l );
    }

    //release list returned by getTriangles()
    void model_instance_writelock::releaseGetTriangles( std::list<model_triangle_instance_ref *> *l )
    {
        model_instance::releaseGetTriangles( l );
    }

    //get triangle vertex instances
    unsigned int model_instance_writelock::getTriangleVertexs( std::list<model_triangle_vertex_instance_ref *> *l )
    {
        return this->t->getTriangleVertexs( l );
    }

    //get triangle vertex instances by triangle
    unsigned int model_instance_writelock::getTriangleVertexsByTriangle( dpid triangle_id, std::list<model_triangle_vertex_instance_ref *> *l )
    {
        return this->t->getTriangleVertexsByTriangle( triangle_id, l );
    }

    //release list returned by getTriangleVertexs()
    void model_instance_writelock::releaseGetTriangleVertexs( std::list<model_triangle_vertex_instance_ref *> *l )
    {
        model_instance::releaseGetTriangleVertexs( l );
    }

    //get vertex instances
    unsigned int model_instance_writelock::getVertexs( std::list<model_vertex_instance_ref *> *l )
    {
        return this->t->getVertexs( l );
    }

    //release list returned by getVertexs()
    void model_instance_writelock::releaseGetVertexs( std::list<model_vertex_instance_ref *> *l )
    {
        model_instance::releaseGetVertexs( l );
    }

};
