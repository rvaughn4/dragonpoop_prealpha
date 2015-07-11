
#include "model_instances.h"
#include "../models.h"
#include "../model_group_instance/model_group_instances.h"
#include "../model_group/model_groups.h"
#include "../model_triangle_instance/model_triangle_instances.h"
#include "../model_triangle/model_triangles.h"
#include "../model_triangle_vertex_instance/model_triangle_vertex_instances.h"
#include "../model_triangle_vertex/model_triangle_vertexes.h"
#include "../model_vertex_instance/model_vertex_instances.h"
#include "../model_vertex/model_vertexes.h"

namespace dragonpoop
{

    //ctor
    model_instance::model_instance( dpthread_lock *thd, model_writelock *ml, dpid id ) : model_component( ml, id,model_component_type_instance, 0 )
    {
        this->makeGroups( thd, ml );
        this->makeTriangles( thd, ml );
        this->makeTriangleVertexs( thd, ml );
        this->makeVertexs( thd, ml );
    }

    //dtor
    model_instance::~model_instance( void )
    {
        this->killGroups();
        this->killTriangles();
        this->killTriangleVertexs();
        this->killVertexs();
    }

    //generate read lock
    shared_obj_readlock *model_instance::genReadLock( shared_obj *p, dpmutex_readlock *l )
    {
        return new model_instance_readlock( (model_instance *)p, l );
    }

    //generate write lock
    shared_obj_writelock *model_instance::genWriteLock( shared_obj *p, dpmutex_writelock *l )
    {
        return new model_instance_writelock( (model_instance *)p, l );
    }

    //generate ref
    shared_obj_ref *model_instance::genRef( shared_obj *p, std::shared_ptr<shared_obj_refkernal> *k )
    {
        return new model_instance_ref( (model_instance *)p, k );
    }

    //do background processing
    void model_instance::onRun( dpthread_lock *thd, gfx_writelock *g, model_writelock *m, model_component_writelock *l )
    {

    }

    //create group instances
    void model_instance::makeGroups( dpthread_lock *thd, model_writelock *ml )
    {
        std::list<model_group_ref *> l;
        std::list<model_group_ref *>::iterator i;
        model_group_ref *p;
        model_group_readlock *pl;
        model_group_instance_ref *r;
        shared_obj_guard o;

        ml->getGroups( &l );

        for( i = l.begin(); i != l.end(); ++i )
        {
            p = *i;
            pl = (model_group_readlock *)o.readLock( p );
            r = ml->createGroupInstance( thd, this->getId(), pl->getId(), pl->getParentId() );
            delete r;
        }

        ml->releaseGetGroups( &l );
    }

    //destroy group instances
    void model_instance::killGroups( void )
    {
        std::list<model_group_instance_ref *> l;
        std::list<model_group_instance_ref *>::iterator i;
        model_group_instance_ref *p;
        model_group_instance_writelock *pl;
        shared_obj_guard o;

        this->getGroups( &l );

        for( i = l.begin(); i != l.end(); ++i )
        {
            p = *i;
            pl = (model_group_instance_writelock *)o.writeLock( p );
            pl->kill();
        }

        model_instance::releaseGetGroups( &l );
    }

    //get group instances
    unsigned int model_instance::getGroups( std::list<model_group_instance_ref *> *l )
    {
        model_readlock *ml;
        model_ref *m;
        shared_obj_guard o;

        m = this->getModel();
        if( !m )
            return 0;
        ml = (model_readlock *)o.readLock( m );
        delete m;
        if( !ml )
            return 0;

        return ml->getGroupInstancesByInstance( this->getId(), l );
    }

    //get group instances by parent
    unsigned int model_instance::getGroupsByParent( dpid parent_id, std::list<model_group_instance_ref *> *l )
    {
        model_readlock *ml;
        model_ref *m;
        shared_obj_guard o;

        m = this->getModel();
        if( !m )
            return 0;
        ml = (model_readlock *)o.readLock( m );
        delete m;
        if( !ml )
            return 0;

        return ml->getGroupInstancesByInstanceAndParent( this->getId(), parent_id, l );
    }

    //release list returned by getGroups()
    void model_instance::releaseGetGroups( std::list<model_group_instance_ref *> *l )
    {
        model::releaseGetGroupInstances( l );
    }

    //create triangle instances
    void model_instance::makeTriangles( dpthread_lock *thd, model_writelock *ml )
    {
        std::list<model_triangle_ref *> l;
        std::list<model_triangle_ref *>::iterator i;
        model_triangle_ref *p;
        model_triangle_readlock *pl;
        model_triangle_instance_ref *r;
        shared_obj_guard o;

        ml->getTriangles( &l );

        for( i = l.begin(); i != l.end(); ++i )
        {
            p = *i;
            pl = (model_triangle_readlock *)o.readLock( p );
            r = ml->createTriangleInstance( thd, this->getId(), pl->getId(), pl->getParentId() );
            delete r;
        }

        ml->releaseGetTriangles( &l );
    }

    //destroy triangle instances
    void model_instance::killTriangles( void )
    {
        std::list<model_triangle_instance_ref *> l;
        std::list<model_triangle_instance_ref *>::iterator i;
        model_triangle_instance_ref *p;
        model_triangle_instance_writelock *pl;
        shared_obj_guard o;

        this->getTriangles( &l );

        for( i = l.begin(); i != l.end(); ++i )
        {
            p = *i;
            pl = (model_triangle_instance_writelock *)o.writeLock( p );
            pl->kill();
        }

        model_instance::releaseGetTriangles( &l );
    }

    //get triangle instances
    unsigned int model_instance::getTriangles( std::list<model_triangle_instance_ref *> *l )
    {
        model_readlock *ml;
        model_ref *m;
        shared_obj_guard o;

        m = this->getModel();
        if( !m )
            return 0;
        ml = (model_readlock *)o.readLock( m );
        delete m;
        if( !ml )
            return 0;

        return ml->getTriangleInstancesByInstance( this->getId(), l );
    }

    //get triangle instances by group
    unsigned int model_instance::getTrianglesByGroup( dpid group_id, std::list<model_triangle_instance_ref *> *l )
    {
        model_readlock *ml;
        model_ref *m;
        shared_obj_guard o;

        m = this->getModel();
        if( !m )
            return 0;
        ml = (model_readlock *)o.readLock( m );
        delete m;
        if( !ml )
            return 0;

        return ml->getTriangleInstancesByInstanceAndGroup( this->getId(), group_id, l );
    }

    //release list returned by getTriangles()
    void model_instance::releaseGetTriangles( std::list<model_triangle_instance_ref *> *l )
    {
        model::releaseGetTriangleInstances( l );
    }

    //create triangle vertex instances
    void model_instance::makeTriangleVertexs( dpthread_lock *thd, model_writelock *ml )
    {
        std::list<model_triangle_vertex_ref *> l;
        std::list<model_triangle_vertex_ref *>::iterator i;
        model_triangle_vertex_ref *p;
        model_triangle_vertex_readlock *pl;
        model_triangle_vertex_instance_ref *r;
        shared_obj_guard o;

        ml->getTriangleVertexes( &l );

        for( i = l.begin(); i != l.end(); ++i )
        {
            p = *i;
            pl = (model_triangle_vertex_readlock *)o.readLock( p );
            r = ml->createTriangleVertexInstance( thd, this->getId(), pl->getId(), pl->getTriangleId(), pl->getVertexId() );
            delete r;
        }

        ml->releaseGetTriangleVertexes( &l );
    }

    //destroy triangle vertex instances
    void model_instance::killTriangleVertexs( void )
    {
        std::list<model_triangle_vertex_instance_ref *> l;
        std::list<model_triangle_vertex_instance_ref *>::iterator i;
        model_triangle_vertex_instance_ref *p;
        model_triangle_vertex_instance_writelock *pl;
        shared_obj_guard o;

        this->getTriangleVertexs( &l );

        for( i = l.begin(); i != l.end(); ++i )
        {
            p = *i;
            pl = (model_triangle_vertex_instance_writelock *)o.writeLock( p );
            pl->kill();
        }

        model_instance::releaseGetTriangleVertexs( &l );
    }

    //get triangle vertex instances
    unsigned int model_instance::getTriangleVertexs( std::list<model_triangle_vertex_instance_ref *> *l )
    {
        model_readlock *ml;
        model_ref *m;
        shared_obj_guard o;

        m = this->getModel();
        if( !m )
            return 0;
        ml = (model_readlock *)o.readLock( m );
        delete m;
        if( !ml )
            return 0;

        return ml->getTriangleVertexInstancesByInstance( this->getId(), l );
    }

    //get triangle vertex instances by triangle
    unsigned int model_instance::getTriangleVertexsByTriangle( dpid triangle_id, std::list<model_triangle_vertex_instance_ref *> *l )
    {
        model_readlock *ml;
        model_ref *m;
        shared_obj_guard o;

        m = this->getModel();
        if( !m )
            return 0;
        ml = (model_readlock *)o.readLock( m );
        delete m;
        if( !ml )
            return 0;

        return ml->getTriangleVertexInstancesByInstanceAndTriangle( this->getId(), triangle_id, l );
    }

    //release list returned by getTriangleVertexs()
    void model_instance::releaseGetTriangleVertexs( std::list<model_triangle_vertex_instance_ref *> *l )
    {
        model::releaseGetTriangleVertexInstances( l );
    }

    //create vertex instances
    void model_instance::makeVertexs( dpthread_lock *thd, model_writelock *ml )
    {
        std::list<model_vertex_ref *> l;
        std::list<model_vertex_ref *>::iterator i;
        model_vertex_ref *p;
        model_vertex_readlock *pl;
        model_vertex_instance_ref *r;
        shared_obj_guard o;

        ml->getVertexes( &l );

        for( i = l.begin(); i != l.end(); ++i )
        {
            p = *i;
            pl = (model_vertex_readlock *)o.readLock( p );
            r = ml->createVertexInstance( thd, this->getId(), pl->getId() );
            delete r;
        }

        ml->releaseGetVertexes( &l );
    }

    //destroy vertex instances
    void model_instance::killVertexs( void )
    {
        std::list<model_vertex_instance_ref *> l;
        std::list<model_vertex_instance_ref *>::iterator i;
        model_vertex_instance_ref *p;
        model_vertex_instance_writelock *pl;
        shared_obj_guard o;

        this->getVertexs( &l );

        for( i = l.begin(); i != l.end(); ++i )
        {
            p = *i;
            pl = (model_vertex_instance_writelock *)o.writeLock( p );
            pl->kill();
        }

        model_instance::releaseGetVertexs( &l );
    }

    //get vertex instances
    unsigned int model_instance::getVertexs( std::list<model_vertex_instance_ref *> *l )
    {
        model_readlock *ml;
        model_ref *m;
        shared_obj_guard o;

        m = this->getModel();
        if( !m )
            return 0;
        ml = (model_readlock *)o.readLock( m );
        delete m;
        if( !ml )
            return 0;

        return ml->getVertexInstancesByInstance( this->getId(), l );
    }

    //release list returned by getVertexs()
    void model_instance::releaseGetVertexs( std::list<model_vertex_instance_ref *> *l )
    {
        model::releaseGetVertexInstances( l );
    }

};
