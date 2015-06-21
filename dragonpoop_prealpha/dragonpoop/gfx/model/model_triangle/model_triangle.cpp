
#include "model_triangle.h"
#include "model_triangle_readlock.h"
#include "model_triangle_writelock.h"
#include "model_triangle_ref.h"
#include "../../../core/shared_obj/shared_obj_guard.h"
#include "../model_ref.h"
#include "../model_writelock.h"

namespace dragonpoop
{

    //ctor
    model_triangle::model_triangle( model_writelock *ml, dpid id, dpid parent_id ) : model_component( ml, id, model_component_type_triangle, 0 )
    {
        this->parent_id = parent_id;
    }

    //dtor
    model_triangle::~model_triangle( void )
    {
        model_component_writelock *l;
        shared_obj_guard g;

        l = (model_component_writelock *)g.writeLock( this );
        g.unlock();
    }

    //generate read lock
    shared_obj_readlock *model_triangle::genReadLock( shared_obj *p, dpmutex_readlock *l )
    {
        return new model_triangle_readlock( (model_triangle *)p, l );
    }

    //generate write lock
    shared_obj_writelock *model_triangle::genWriteLock( shared_obj *p, dpmutex_writelock *l )
    {
        return new model_triangle_writelock( (model_triangle *)p, l );
    }

    //generate ref
    shared_obj_ref *model_triangle::genRef( shared_obj *p, std::shared_ptr<shared_obj_refkernal> *k )
    {
        return new model_triangle_ref( (model_triangle *)p, k );
    }

    //do background processing
    void model_triangle::onRun( dpthread_lock *thd, gfx_writelock *g, model_writelock *m, model_component_writelock *l )
    {

    }

    //get parent id
    dpid model_triangle::getParentId( void )
    {
        return this->parent_id;
    }

    //get parent
    model_group_ref *model_triangle::getParent( void )
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

};
