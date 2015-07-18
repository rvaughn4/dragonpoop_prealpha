
#include "model_triangle_vertex_instance.h"
#include "model_triangle_vertex_instance_readlock.h"
#include "model_triangle_vertex_instance_writelock.h"
#include "model_triangle_vertex_instance_ref.h"
#include "../model_vertex_instance/model_vertex_instance_ref.h"
#include "../model_vertex_instance/model_vertex_instance_readlock.h"
#include "../model_ref.h"
#include "../model_writelock.h"
#include "../model_triangle_vertex/model_triangle_vertex_ref.h"
#include "../model_triangle_vertex/model_triangle_vertex_readlock.h"

namespace dragonpoop
{

    //ctor
    model_triangle_vertex_instance::model_triangle_vertex_instance( model_writelock *ml, dpid id, dpid instance_id, dpid triangle_vertex_id, dpid triangle_id, dpid vertex_id ) : model_component( ml, id,model_component_type_triangle_vertex_instance, 0 )
    {
        this->instance_id = instance_id;
        this->triangle_id = triangle_id;
        this->vertex_id = vertex_id;
        this->triangle_vertex_id = triangle_vertex_id;
        this->sync( ml );
    }

    //dtor
    model_triangle_vertex_instance::~model_triangle_vertex_instance( void )
    {

    }

    //generate read lock
    shared_obj_readlock *model_triangle_vertex_instance::genReadLock( shared_obj *p, dpmutex_readlock *l )
    {
        return new model_triangle_vertex_instance_readlock( (model_triangle_vertex_instance *)p, l );
    }

    //generate write lock
    shared_obj_writelock *model_triangle_vertex_instance::genWriteLock( shared_obj *p, dpmutex_writelock *l )
    {
        return new model_triangle_vertex_instance_writelock( (model_triangle_vertex_instance *)p, l );
    }

    //generate ref
    shared_obj_ref *model_triangle_vertex_instance::genRef( shared_obj *p, std::shared_ptr<shared_obj_refkernal> *k )
    {
        return new model_triangle_vertex_instance_ref( (model_triangle_vertex_instance *)p, k );
    }

    //do background processing
    void model_triangle_vertex_instance::onRun( dpthread_lock *thd, gfx_writelock *g, model_writelock *m, model_component_writelock *l )
    {

    }

    //return instance id
    dpid model_triangle_vertex_instance::getInstanceId( void )
    {
        return this->instance_id;
    }

    //return triangle id
    dpid model_triangle_vertex_instance::getTriangleId( void )
    {
        return this->triangle_id;
    }

    //return vertex id
    dpid model_triangle_vertex_instance::getVertexId( void )
    {
        return this->vertex_id;
    }

    //return triangle vertex id
    dpid model_triangle_vertex_instance::getTriangleVertexId( void )
    {
        return this->triangle_vertex_id;
    }

    //get vertexes
    void model_triangle_vertex_instance::getVertex( model_writelock *ml, dpvertexindex_buffer *b )
    {
        std::list<model_vertex_instance_ref *> l;
        std::list<model_vertex_instance_ref *>::iterator i;
        model_vertex_instance_ref *p;
        model_vertex_instance_readlock *pl;
        shared_obj_guard o, om;
        dpvertex v;

        ml->getVertexInstancesByInstanceAndVertex( this->getInstanceId(), this->getVertexId(), &l );

        for( i = l.begin(); i != l.end(); ++i )
        {
            p = *i;
            pl = (model_vertex_instance_readlock *)o.readLock( p );

            v.start.texcoords[ 0 ] = this->texcoords[ 0 ];
            v.start.texcoords[ 1 ] = this->texcoords[ 1 ];
            v.end.texcoords[ 0 ] = this->texcoords[ 0 ];
            v.end.texcoords[ 1 ] = this->texcoords[ 1 ];

            v.start.normal = this->norm[ 0 ];
            v.end.normal = this->norm[ 1 ];

            pl->getVertex( ml, &v );
           // b->addVertex( &v, pl->getVertexId() );
        }

        ml->releaseGetVertexInstances( &l );
    }


    //sync vertex
    void model_triangle_vertex_instance::sync( model_writelock *ml )
    {
        model_triangle_vertex_ref *v;
        model_triangle_vertex_readlock *vl;
        shared_obj_guard o;

        v = ml->findTriangleVertex( this->getTriangleVertexId() );
        if( !v )
            return;
        vl = (model_triangle_vertex_readlock *)o.readLock( v );
        delete v;

        vl->getTexcoord( 0, &this->texcoords[ 0 ] );
        vl->getTexcoord( 1, &this->texcoords[ 1 ] );
        vl->getNormal( &this->norm[ 0 ] );

        this->norm[ 1 ] = this->norm[ 0 ];
    }

};
