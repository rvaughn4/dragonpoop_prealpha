
#include "model_joint.h"
#include "model_joint_ref.h"
#include "model_joint_readlock.h"
#include "model_joint_writelock.h"
#include "../model_ref.h"
#include "../model_readlock.h"

namespace dragonpoop
{

    //ctor
    model_joint::model_joint( model_writelock *ml, dpid id ) : model_component( ml, id, model_component_type_joint, 0 )
    {
    }

    //dtor
    model_joint::~model_joint( void )
    {
        model_component_writelock *l;
        shared_obj_guard g;

        l = (model_component_writelock *)g.writeLock( this );
        g.unlock();
    }

    //generate read lock
    shared_obj_readlock *model_joint::genReadLock( shared_obj *p, dpmutex_readlock *l )
    {
        return new model_joint_readlock( (model_joint *)p, l );
    }

    //generate write lock
    shared_obj_writelock *model_joint::genWriteLock( shared_obj *p, dpmutex_writelock *l )
    {
        return new model_joint_writelock( (model_joint *)p, l );
    }

    //generate ref
    shared_obj_ref *model_joint::genRef( shared_obj *p, std::shared_ptr<shared_obj_refkernal> *k )
    {
        return new model_joint_ref( (model_joint *)p, k );
    }

    //do background processing
    void model_joint::onRun( dpthread_lock *thd, gfx_writelock *g, model_writelock *m, model_component_writelock *l )
    {

    }

    //get position
    void model_joint::getPosition( dpxyzw *p )
    {
        *p = this->pos;
    }

    //get roatation
    void model_joint::getRotation( dpxyzw *p )
    {
        *p = this->rot;
    }

    //get name
    void model_joint::getName( std::string *s )
    {
        *s = this->sname;
    }

    //set position
    void model_joint::setPosition( dpxyzw *p )
    {
        this->pos = *p;
    }

    //set roatation
    void model_joint::setRotation( dpxyzw *p )
    {
        this->rot = *p;
    }

    //set name
    void model_joint::setName( std::string *s )
    {
        this->sname = *s;
    }

};
