
#include "model_group_instance.h"
#include "model_group_instance_readlock.h"
#include "model_group_instance_writelock.h"
#include "model_group_instance_ref.h"

namespace dragonpoop
{

    //ctor
    model_group_instance::model_group_instance( model_writelock *ml, dpid id, dpid instance_id, dpid group_id, dpid parent_id ) : model_component( ml, id,model_component_type_group_instance, 0 )
    {
        this->instance_id = instance_id;
        this->group_id = group_id;
        this->parent_id = parent_id;
    }

    //dtor
    model_group_instance::~model_group_instance( void )
    {

    }

    //generate read lock
    shared_obj_readlock *model_group_instance::genReadLock( shared_obj *p, dpmutex_readlock *l )
    {
        return new model_group_instance_readlock( (model_group_instance *)p, l );
    }

    //generate write lock
    shared_obj_writelock *model_group_instance::genWriteLock( shared_obj *p, dpmutex_writelock *l )
    {
        return new model_group_instance_writelock( (model_group_instance *)p, l );
    }

    //generate ref
    shared_obj_ref *model_group_instance::genRef( shared_obj *p, std::shared_ptr<shared_obj_refkernal> *k )
    {
        return new model_group_instance_ref( (model_group_instance *)p, k );
    }

    //do background processing
    void model_group_instance::onRun( dpthread_lock *thd, gfx_writelock *g, model_writelock *m, model_component_writelock *l )
    {

    }

    //return instance id
    dpid model_group_instance::getInstanceId( void )
    {
        return this->instance_id;
    }

    //return vertex id
    dpid model_group_instance::getGroupId( void )
    {
        return this->group_id;
    }

    //return partent id
    dpid model_group_instance::getParentId( void )
    {
        return this->parent_id;
    }

    //returns true if has renderer
    bool model_group_instance::hasRenderer( void )
    {
        if( !this->r || !this->r->isLinked() )
            return 0;
        return 1;
    }

    //set renderer
    void model_group_instance::setRenderer( shared_obj_writelock *r )
    {
        if( this->r )
            delete this->r;
        this->r = r->getRef();
    }

    //get renderer
    shared_obj_ref *model_group_instance::getRenderer( void )
    {
        shared_obj_writelock *l;
        shared_obj_guard o;
        if( !this->r )
            return 0;
        l = o.writeLock( this->r );
        if( !l )
            return 0;
        return l->getRef();
    }

};
