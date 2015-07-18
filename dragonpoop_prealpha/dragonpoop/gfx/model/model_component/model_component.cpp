
#include "model_component.h"
#include "../../../core/core.h"
#include "model_writelock.h"
#include "model_ref.h"
#include "model_component_readlock.h"
#include "model_component_writelock.h"
#include "model_component_ref.h"
#include "../../../core/dpthread/dpthread_lock.h"
#include "../../../core/shared_obj/shared_obj_guard.h"

#include <iostream>

namespace dragonpoop
{


    //ctor
    model_component::model_component( model_writelock *ml, dpid id, uint16_t ctype, uint64_t run_wait ) : shared_obj( ml->getCore()->getMutexMaster() )
    {
        this->c = ml->getCore();
        this->m = (model_ref *)ml->getRef();
        this->bAlive = 1;
        this->id = id;
        this->ctype = ctype;
        this->run_wait = run_wait;
        this->last_run = 0;
    }

    //dtor
    model_component::~model_component( void )
    {
        model_component_writelock *l;
        shared_obj_guard g;

        l = (model_component_writelock *)g.writeLock( this );
        g.unlock();

        delete this->m;
    }

    //generate read lock
    shared_obj_readlock *model_component::genReadLock( shared_obj *p, dpmutex_readlock *l )
    {
        return new model_component_readlock( (model_component *)p, l );
    }

    //generate write lock
    shared_obj_writelock *model_component::genWriteLock( shared_obj *p, dpmutex_writelock *l )
    {
        return new model_component_writelock( (model_component *)p, l );
    }

    //generate ref
    shared_obj_ref *model_component::genRef( shared_obj *p, std::shared_ptr<shared_obj_refkernal> *k )
    {
        return new model_component_ref( (model_component *)p, k );
    }

    //return core
    core *model_component::getCore( void )
    {
        return this->c;
    }

    //returns true if alive
    bool model_component::isAlive( void )
    {
        return this->bAlive;
    }

    //get id
    dpid model_component::getId( void )
    {
        return this->id;
    }

    //get type
    uint16_t model_component::getType( void )
    {
        return this->ctype;
    }

    //kill model
    void model_component::kill( void )
    {
        this->bAlive = 0;
    }

    //run model
    void model_component::run( dpthread_lock *thd, gfx_writelock *g, model_writelock *m, model_component_writelock *l )
    {
        uint64_t t, td;

        if( !this->run_wait )
            return;

        t = thd->getTicks();
        td = t - this->last_run;
        if( td < this->run_wait )
            return;
        std::cout << td << "\r\n";

        this->last_run = t;
        this->onRun( thd, g, m, l );
    }

    //do background processing
    void model_component::onRun( dpthread_lock *thd, gfx_writelock *g, model_writelock *m, model_component_writelock *l )
    {

    }

    //return model
    model_ref *model_component::getModel( void )
    {
        shared_obj_guard g;
        model_writelock *ml;
        ml = (model_writelock *)g.writeLock( this->m );
        return (model_ref *)ml->getRef();
    }

    //get comment
    void model_component::getComment( std::string *s )
    {
        *s = this->scomment;
    }

    //set comment
    void model_component::setComment( std::string *s )
    {
        this->scomment = *s;
    }

    //add comment
    void model_component::addComment( std::string *s )
    {
        this->scomment.append( *s );
    }

};

