
#include "model_vertex_joint_instance.h"
#include "model_vertex_joint_instance_readlock.h"
#include "model_vertex_joint_instance_writelock.h"
#include "model_vertex_joint_instance_ref.h"

namespace dragonpoop
{

    //ctor
    model_vertex_joint_instance::model_vertex_joint_instance( model_writelock *ml, dpid id, dpid instance_id, dpid vertex_joint_id, dpid joint_id, dpid vertex_id ) : model_component( ml, id,model_component_type_vertex_joint_instance, 0 )
    {
        this->instance_id = instance_id;
        this->vertex_joint_id = vertex_joint_id;
        this->joint_id = joint_id;
        this->vertex_id = vertex_id;
    }

    //dtor
    model_vertex_joint_instance::~model_vertex_joint_instance( void )
    {

    }

    //generate read lock
    shared_obj_readlock *model_vertex_joint_instance::genReadLock( shared_obj *p, dpmutex_readlock *l )
    {
        return new model_vertex_joint_instance_readlock( (model_vertex_joint_instance *)p, l );
    }

    //generate write lock
    shared_obj_writelock *model_vertex_joint_instance::genWriteLock( shared_obj *p, dpmutex_writelock *l )
    {
        return new model_vertex_joint_instance_writelock( (model_vertex_joint_instance *)p, l );
    }

    //generate ref
    shared_obj_ref *model_vertex_joint_instance::genRef( shared_obj *p, std::shared_ptr<shared_obj_refkernal> *k )
    {
        return new model_vertex_joint_instance_ref( (model_vertex_joint_instance *)p, k );
    }

    //do background processing
    void model_vertex_joint_instance::onRun( dpthread_lock *thd, gfx_writelock *g, model_writelock *m, model_component_writelock *l )
    {

    }

    //return instance id
    dpid model_vertex_joint_instance::getInstanceId( void )
    {
        return this->instance_id;
    }

    //return vertex joint id
    dpid model_vertex_joint_instance::getVertexJointId( void )
    {
        return this->vertex_joint_id;
    }

    //return joint id
    dpid model_vertex_joint_instance::getJointId( void )
    {
        return this->joint_id;
    }

    //return vertex id
    dpid model_vertex_joint_instance::getVertexId( void )
    {
        return this->vertex_id;
    }
    
};
