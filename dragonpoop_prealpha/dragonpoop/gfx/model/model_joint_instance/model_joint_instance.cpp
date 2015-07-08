
#include "model_joint_instance.h"
#include "model_joint_instance_readlock.h"
#include "model_joint_instance_writelock.h"
#include "model_joint_instance_ref.h"

namespace dragonpoop
{

    //ctor
    model_joint_instance::model_joint_instance( model_writelock *ml, dpid id, dpid instance_id, dpid joint_id ) : model_component( ml, id,model_component_type_joint_instance, 0 )
    {
        this->instance_id = instance_id;
        this->joint_id = joint_id;
    }

    //dtor
    model_joint_instance::~model_joint_instance( void )
    {

    }

    //generate read lock
    shared_obj_readlock *model_joint_instance::genReadLock( shared_obj *p, dpmutex_readlock *l )
    {
        return new model_joint_instance_readlock( (model_joint_instance *)p, l );
    }

    //generate write lock
    shared_obj_writelock *model_joint_instance::genWriteLock( shared_obj *p, dpmutex_writelock *l )
    {
        return new model_joint_instance_writelock( (model_joint_instance *)p, l );
    }

    //generate ref
    shared_obj_ref *model_joint_instance::genRef( shared_obj *p, std::shared_ptr<shared_obj_refkernal> *k )
    {
        return new model_joint_instance_ref( (model_joint_instance *)p, k );
    }

    //do background processing
    void model_joint_instance::onRun( dpthread_lock *thd, gfx_writelock *g, model_writelock *m, model_component_writelock *l )
    {

    }

    //return instance id
    dpid model_joint_instance::getInstanceId( void )
    {
        return this->instance_id;
    }

    //return joint id
    dpid model_joint_instance::getJointId( void )
    {
        return this->joint_id;
    }
    
};
