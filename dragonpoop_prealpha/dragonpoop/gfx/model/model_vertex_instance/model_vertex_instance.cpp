
#include "model_vertex_instance.h"
#include "model_vertex_instance_readlock.h"
#include "model_vertex_instance_writelock.h"
#include "model_vertex_instance_ref.h"
#include "../model_Vertex/model_vertex_ref.h"
#include "../model_Vertex/model_vertex_readlock.h"
#include "../model_ref.h"
#include "../model_writelock.h"

namespace dragonpoop
{

    //ctor
    model_vertex_instance::model_vertex_instance( model_writelock *ml, dpid id, dpid instance_id, dpid vertex_id ) : model_component( ml, id,model_component_type_vertex_instance, 0 )
    {
        this->instance_id = instance_id;
        this->vertex_id = vertex_id;
        this->sync( ml );
    }

    //dtor
    model_vertex_instance::~model_vertex_instance( void )
    {

    }

    //generate read lock
    shared_obj_readlock *model_vertex_instance::genReadLock( shared_obj *p, dpmutex_readlock *l )
    {
        return new model_vertex_instance_readlock( (model_vertex_instance *)p, l );
    }

    //generate write lock
    shared_obj_writelock *model_vertex_instance::genWriteLock( shared_obj *p, dpmutex_writelock *l )
    {
        return new model_vertex_instance_writelock( (model_vertex_instance *)p, l );
    }

    //generate ref
    shared_obj_ref *model_vertex_instance::genRef( shared_obj *p, std::shared_ptr<shared_obj_refkernal> *k )
    {
        return new model_vertex_instance_ref( (model_vertex_instance *)p, k );
    }

    //do background processing
    void model_vertex_instance::onRun( dpthread_lock *thd, gfx_writelock *g, model_writelock *m, model_component_writelock *l )
    {
        
    }

    //return instance id
    dpid model_vertex_instance::getInstanceId( void )
    {
        return this->instance_id;
    }

    //return vertex id
    dpid model_vertex_instance::getVertexId( void )
    {
        return this->vertex_id;
    }

    //get vertex data
    void model_vertex_instance::getVertex( model_writelock *ml, dpvertex *v )
    {
        v->start.pos = this->pos[ 0 ];
        v->end.pos = this->pos[ 1 ];
    }

    //sync vertex
    void model_vertex_instance::sync( model_writelock *ml )
    {
        model_vertex_ref *v;
        model_vertex_readlock *vl;
        shared_obj_guard o;

        v = ml->findVertex( this->getVertexId() );
        if( !v )
            return;
        vl = (model_vertex_readlock *)o.readLock( v );
        delete v;

        vl->getPosition( &this->pos[ 0 ] );
        this->pos[ 1 ] = this->pos[ 0 ];
    }

};
