
#include "model_triangle_instance.h"
#include "model_triangle_instance_readlock.h"
#include "model_triangle_instance_writelock.h"
#include "model_triangle_instance_ref.h"
#include "../model_triangle_vertex_instance/model_triangle_vertex_instance_ref.h"
#include "../model_triangle_vertex_instance/model_triangle_vertex_instance_readlock.h"
#include "../model_ref.h"
#include "../model_writelock.h"

namespace dragonpoop
{

    //ctor
    model_triangle_instance::model_triangle_instance( model_writelock *ml, dpid id, dpid instance_id, dpid triangle_id, dpid group_id ) : model_component( ml, id,model_component_type_triangle_instance, 0 )
    {
        this->instance_id = instance_id;
        this->triangle_id = triangle_id;
        this->group_id = group_id;
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
        std::list<model_triangle_vertex_instance_ref *> l;
        std::list<model_triangle_vertex_instance_ref *>::iterator i;
        model_triangle_vertex_instance_ref *p;
        model_triangle_vertex_instance_readlock *pl;
        shared_obj_guard o;

        ml->getTriangleVertexInstancesByInstanceAndTriangle( this->getInstanceId(), this->getTriangleId(), &l );

        for( i = l.begin(); i != l.end(); ++i )
        {
            p = *i;
            pl = (model_triangle_vertex_instance_readlock *)o.readLock( p );
            pl->getVertex( ml, b );
        }

        ml->releaseGetTriangleVertexInstances( &l );
    }

};
