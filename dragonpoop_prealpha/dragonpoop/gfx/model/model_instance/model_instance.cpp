
#include "model_instance.h"
#include "model_instance_readlock.h"
#include "model_instance_writelock.h"
#include "model_instance_ref.h"

namespace dragonpoop
{

    //ctor
    model_instance::model_instance( model_writelock *ml, dpid id ) : model_component( ml, id,model_component_type_instance, 0 )
    {

    }

    //dtor
    model_instance::~model_instance( void )
    {

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

};
