
#include "model_group.h"
#include "model_group_readlock.h"
#include "model_group_writelock.h"
#include "model_group_ref.h"
#include "../../../core/shared_obj/shared_obj_guard.h"
#include "../model_ref.h"
#include "../model_writelock.h"

namespace dragonpoop
{

    //ctor
    model_group::model_group( model_writelock *ml, dpid id, dpid parent_id ) : model_component( ml, id, model_component_type_group, 0 )
    {
        this->parent_id = parent_id;
        dpid_zero( &this->material_id );
    }

    //dtor
    model_group::~model_group( void )
    {
        model_component_writelock *l;
        shared_obj_guard g;

        l = (model_component_writelock *)g.writeLock( this );
        g.unlock();
    }

    //generate read lock
    shared_obj_readlock *model_group::genReadLock( shared_obj *p, dpmutex_readlock *l )
    {
        return new model_group_readlock( (model_group *)p, l );
    }

    //generate write lock
    shared_obj_writelock *model_group::genWriteLock( shared_obj *p, dpmutex_writelock *l )
    {
        return new model_group_writelock( (model_group *)p, l );
    }

    //generate ref
    shared_obj_ref *model_group::genRef( shared_obj *p, std::shared_ptr<shared_obj_refkernal> *k )
    {
        return new model_group_ref( (model_group *)p, k );
    }

    //do background processing
    void model_group::onRun( dpthread_lock *thd, gfx_writelock *g, model_writelock *m, model_component_writelock *l )
    {

    }

    //get parent id
    dpid model_group::getParentId( void )
    {
        return this->parent_id;
    }

    //get parent
    model_group_ref *model_group::getParent( void )
    {
        shared_obj_guard g;
        model_writelock *ml;
        model_ref *m;

        if( dpid_isZero( &this->parent_id ) )
            return 0;

        m = this->getModel();
        if( !m )
            return 0;
        ml = (model_writelock *)g.writeLock( m );
        delete m;
        if( !ml )
            return 0;
        return ml->findGroup( this->parent_id );
    }

    //get name
    void model_group::getName( std::string *s )
    {
        *s = this->sname;
    }

    //set name
    void model_group::setName( std::string *s )
    {
        this->sname = *s;
    }

    //set material id
    void model_group::setMaterialId( dpid id )
    {
        this->material_id = id;
    }

    //get material id
    dpid model_group::getMaterialId( void )
    {
        return this->material_id;
    }

    //returns true if has material
    bool model_group::hasMaterial( void )
    {
        return !dpid_isZero( &this->material_id );
    }

};
