
#include "model_triangle_instance.h"
#include "model_triangle_instance_readlock.h"
#include "model_triangle_instance_writelock.h"
#include "model_triangle_instance_ref.h"
#include "../model_ref.h"
#include "../model_writelock.h"
#include "../model_triangle_vertex/model_triangle_vertex_ref.h"
#include "../model_triangle_vertex/model_triangle_vertex_readlock.h"
#include "../model_vertex/model_vertex_ref.h"
#include "../model_vertex/model_vertex_readlock.h"

namespace dragonpoop
{

    //ctor
    model_triangle_instance::model_triangle_instance( model_writelock *ml, dpid id, dpid instance_id, dpid triangle_id, dpid group_id ) : model_component( ml, id,model_component_type_triangle_instance, 0 )
    {
        this->instance_id = instance_id;
        this->triangle_id = triangle_id;
        this->group_id = group_id;
        this->isLoaded = 0;
        this->sync( ml );
    }

    //dtor
    model_triangle_instance::~model_triangle_instance( void )
    {

    }

    //generate read lock
    shared_obj_readlock *model_triangle_instance::genReadLock( shared_obj *p, dpmutex_readlock *l )
    {
        return new model_triangle_instance_readlock( (model_triangle_instance *)p, l );
    }

    //generate write lock
    shared_obj_writelock *model_triangle_instance::genWriteLock( shared_obj *p, dpmutex_writelock *l )
    {
        return new model_triangle_instance_writelock( (model_triangle_instance *)p, l );
    }

    //generate ref
    shared_obj_ref *model_triangle_instance::genRef( shared_obj *p, std::shared_ptr<shared_obj_refkernal> *k )
    {
        return new model_triangle_instance_ref( (model_triangle_instance *)p, k );
    }

    //do background processing
    void model_triangle_instance::onRun( dpthread_lock *thd, gfx_writelock *g, model_writelock *m, model_component_writelock *l )
    {

    }

    //return instance id
    dpid model_triangle_instance::getInstanceId( void )
    {
        return this->instance_id;
    }

    //return triangle id
    dpid model_triangle_instance::getTriangleId( void )
    {
        return this->triangle_id;
    }

    //return group id
    dpid model_triangle_instance::getGroupId( void )
    {
        return this->group_id;
    }

    //get vertexes
    void model_triangle_instance::getVertexes( model_writelock *ml, dpvertexindex_buffer *b )
    {
        model_triangle_instance_vert *v;
        unsigned int i;

        for( i = 0; i < 3; i++ )
        {
            v = &this->vert[ i ];
            b->addVertex( &v->trans_data, v->vertex_id );
        }
    }

    //sync triangle
    void model_triangle_instance::sync( model_writelock *ml )
    {
        std::list<model_triangle_vertex_ref *> tl;
        std::list<model_triangle_vertex_ref *>::iterator ti;
        model_triangle_vertex_ref *tv;
        model_triangle_vertex_readlock *tvl;
        shared_obj_guard o;
        unsigned int i;
        model_triangle_instance_vert *p;
        model_vertex_ref *v;
        model_vertex_readlock *vl;

        if( !this->isLoaded )
        {

            ml->getTriangleVertexesByTriangle( &tl, this->getTriangleId() );

            for( i = 0, ti = tl.begin(); ti != tl.end(); ++ti, i++ )
            {
                tv = *ti;
                tvl = (model_triangle_vertex_readlock *)o.tryReadLock( tv, 100 );
                if( !tvl )
                    continue;
                if( i >= 3 )
                    continue;
                p = &this->vert[ i ];
                p->vertex_id = tvl->getVertexId();
                p->triagnle_vertex_id = tvl->getId();
                tvl->getNormal( &p->orig_data.start.normal );
                tvl->getNormal( &p->orig_data.end.normal );
                tvl->getTexcoord( 0, &p->orig_data.start.texcoords[ 0 ] );
                tvl->getTexcoord( 1, &p->orig_data.start.texcoords[ 1 ] );
                tvl->getTexcoord( 0, &p->orig_data.end.texcoords[ 0 ] );
                tvl->getTexcoord( 1, &p->orig_data.end.texcoords[ 1 ] );
            }

            ml->releaseGetTriangleVertexes( &tl );

            for( i = 0; i < 3; i++ )
            {
                p = &this->vert[ i ];
                v = ml->findVertex( p->vertex_id );
                if( !v )
                    continue;
                vl = (model_vertex_readlock *)o.tryReadLock( v, 100 );
                delete v;
                if( !vl )
                    continue;
                
                //            p->joint_id =
                vl->getPosition( &p->orig_data.start.pos );
                vl->getPosition( &p->orig_data.end.pos );
            }

            this->isLoaded = 1;
        }

        for( i = 0; i < 3; i++ )
        {
            p = &this->vert[ i ];
            p->trans_data = p->orig_data;
        }
    }

};
