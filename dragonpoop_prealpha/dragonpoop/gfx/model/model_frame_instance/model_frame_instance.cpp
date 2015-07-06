
#include "model_frame_instance.h"
#include "model_frame_instance_readlock.h"
#include "model_frame_instance_writelock.h"
#include "model_frame_instance_ref.h"

namespace dragonpoop
{

    //ctor
    model_frame_instance::model_frame_instance( model_writelock *ml, dpid id, dpid instance_id, dpid frame_id ) : model_component( ml, id,model_component_type_frame_instance, 0 )
    {
        this->instance_id = instance_id;
        this->frame_id = frame_id;
    }

    //dtor
    model_frame_instance::~model_frame_instance( void )
    {

    }

    //generate read lock
    shared_obj_readlock *model_frame_instance::genReadLock( shared_obj *p, dpmutex_readlock *l )
    {
        return new model_frame_instance_readlock( (model_frame_instance *)p, l );
    }

    //generate write lock
    shared_obj_writelock *model_frame_instance::genWriteLock( shared_obj *p, dpmutex_writelock *l )
    {
        return new model_frame_instance_writelock( (model_frame_instance *)p, l );
    }

    //generate ref
    shared_obj_ref *model_frame_instance::genRef( shared_obj *p, std::shared_ptr<shared_obj_refkernal> *k )
    {
        return new model_frame_instance_ref( (model_frame_instance *)p, k );
    }

    //do background processing
    void model_frame_instance::onRun( dpthread_lock *thd, gfx_writelock *g, model_writelock *m, model_component_writelock *l )
    {

    }

    //return instance id
    dpid model_frame_instance::getInstanceId( void )
    {
        return this->instance_id;
    }

    //return vertex id
    dpid model_frame_instance::getFrameId( void )
    {
        return this->frame_id;
    }
    
};
