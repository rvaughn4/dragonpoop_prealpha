
#include "model_triangle_vertex_instance.h"
#include "model_triangle_vertex_instance_readlock.h"
#include "model_triangle_vertex_instance_writelock.h"
#include "model_triangle_vertex_instance_ref.h"

namespace dragonpoop
{

    //ctor
    model_triangle_vertex_instance::model_triangle_vertex_instance( model_writelock *ml, dpid id, dpid instance_id ) : model_component( ml, id,model_component_type_triangle_vertex_instance, 0 )
    {
        this->instance_id = instance_id;
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
    
};
