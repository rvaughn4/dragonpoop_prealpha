
#include "gfx_writelock.h"
#include "gfx.h"

namespace dragonpoop
{

    //ctor
    gfx_writelock::gfx_writelock( gfx *t, dpmutex_writelock *l ) : shared_obj_writelock( t, l )
    {
        this->t = t;
    }

    //dtor
    gfx_writelock::~gfx_writelock( void )
    {

    }

    //returns true if running
    bool gfx_writelock::isRunning( void )
    {
        return this->t->isRunning();
    }

    //return core
    core *gfx_writelock::getCore( void )
    {
        return this->t->getCore();
    }

    //stop gfx task
    void gfx_writelock::kill( void )
    {
        this->t->kill();
    }

    //run gfx from task
    void gfx_writelock::run( dpthread_lock *thd )
    {
        this->t->run( thd, this );
    }

    //find model by id
    model_ref *gfx_writelock::findModel( dpid id )
    {
        return this->t->findModel( id );
    }

    //find model by name
    model_ref *gfx_writelock::findModel( const char *c )
    {
        return this->t->findModel( c );
    }

    //create model
    model_ref *gfx_writelock::createModel( dpthread_lock *thd )
    {
        return this->t->createModel( thd, this );
    }

    //create model having name
    model_ref *gfx_writelock::createModel( dpthread_lock *thd, const char *cname )
    {
        return this->t->createModel( thd, this, cname );
    }

    //create model having id
    model_ref *gfx_writelock::createModel( dpthread_lock *thd, dpid id )
    {
        return this->t->createModel( thd, this, id );
    }

    //create model having id and name
    model_ref *gfx_writelock::createModel( dpthread_lock *thd, dpid id, const char *cname )
    {
        return this->t->createModel( thd, this, id, cname );
    }

};
