
#include "model_readlock.h"
#include "model.h"

namespace dragonpoop
{

    //ctor
    model_readlock::model_readlock( model *t, dpmutex_readlock *l ) : shared_obj_readlock( t, l )
    {
        this->t = t;
    }

    //dtor
    model_readlock::~model_readlock( void )
    {

    }

    //return core
    core *model_readlock::getCore( void )
    {
        return this->t->getCore();
    }

    //get name
    void model_readlock::getName( std::string *s )
    {
        this->t->getName( s );
    }

    //get id
    dpid model_readlock::getId( void )
    {
        return this->t->getId();
    }

    //returns true if alive
    bool model_readlock::isAlive( void )
    {
        return this->t->isAlive();
    }

    //get all vertexes
    unsigned int model_readlock::getVertexes( std::list<model_vertex_ref *> *l )
    {
        return this->t->getVertexes( l );
    }

    //release list returned by getVertexes()
    void model_readlock::releaseGetVertexes( std::list<model_vertex_ref *> *l )
    {
        model::releaseGetVertexes( l );
    }

    //find a vertex by id
    model_vertex_ref *model_readlock::findVertex( dpid id )
    {
        return this->t->findVertex( id );
    }

    //find a group by id
    model_group_ref *model_readlock::findGroup( dpid id )
    {
        return this->t->findGroup( id );
    }

    //get all groups
    unsigned int model_readlock::getGroups( std::list<model_group_ref *> *l )
    {
        return this->t->getGroups( l );
    }

    //get all groups
    unsigned int model_readlock::getGroupsByParent( std::list<model_group_ref *> *l, dpid parent_id )
    {
        return this->t->getGroupsByParent( l, parent_id );
    }

    //release list returned by getGroups()
    void model_readlock::releaseGetGroups( std::list<model_group_ref *> *l )
    {
        model::releaseGetGroups( l );
    }

    //find a triangle by id
    model_triangle_ref *model_readlock::findTriangle( dpid id )
    {
        return this->t->findTriangle( id );
    }

    //get all triangles
    unsigned int model_readlock::getTriangles( std::list<model_triangle_ref *> *l )
    {
        return this->t->getTriangles( l );
    }

    //get all triangles belonging to group
    unsigned int model_readlock::getTrianglesByGroup( std::list<model_triangle_ref *> *l, dpid group_id )
    {
        return this->t->getTrianglesByGroup( l, group_id );
    }

    //release list returned by getTriangles()
    void model_readlock::releaseGetTriangles( std::list<model_triangle_ref *> *l )
    {
        model::releaseGetTriangles( l );
    }

    //find a triangle vertex by id
    model_triangle_vertex_ref *model_readlock::findTriangleVertex( dpid id )
    {
        return this->t->findTriangleVertex( id );
    }

    //get all triangle vertexes
    unsigned int model_readlock::getTriangleVertexes( std::list<model_triangle_vertex_ref *> *l )
    {
        return this->t->getTriangleVertexes( l );
    }

    //get all triangle vertexes belonging to triangle
    unsigned int model_readlock::getTriangleVertexesByTriangle( std::list<model_triangle_vertex_ref *> *l, dpid triangle_id )
    {
        return this->t->getTriangleVertexesByTriangle( l, triangle_id );
    }

    //get all triangle vertexes belonging to vertex
    unsigned int model_readlock::getTriangleVertexesByVertex( std::list<model_triangle_vertex_ref *> *l, dpid vertex_id )
    {
        return this->t->getTriangleVertexesByVertex( l, vertex_id );
    }

    //release list returned by getTriangleVertexes()
    void model_readlock::releaseGetTriangleVertexes( std::list<model_triangle_vertex_ref *> *l )
    {
        model::releaseGetTriangleVertexes( l );
    }

};
