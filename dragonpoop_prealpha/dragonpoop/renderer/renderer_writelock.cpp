
#include "renderer_writelock.h"
#include "renderer.h"

namespace dragonpoop
{

    //ctor
    renderer_writelock::renderer_writelock( renderer *t, dpmutex_writelock *l ) : shared_obj_writelock( t, l )
    {
        this->t = t;
    }

    //dtor
    renderer_writelock::~renderer_writelock( void )
    {

    }

    //returns true if running
    bool renderer_writelock::isRunning( void )
    {
        return this->t->isRunning();
    }

    //return core
    core *renderer_writelock::getCore( void )
    {
        return this->t->getCore();
    }

    //stop renderer task
    void renderer_writelock::kill( void )
    {
        this->t->kill();
    }

    //run renderer from task
    void renderer_writelock::run( dptask_writelock *tskl, dpthread_lock *thd )
    {
        this->t->run( tskl, thd );
    }

    //generate model instance
    renderer_model_instance *renderer_writelock::genModel( gfx_writelock *g, model_instance_writelock *m )
    {
        return this->t->genModel( g, this, m );
    }

    //generate model group instance
    renderer_model_group_instance *renderer_writelock::genGroup( gfx_writelock *g, model_instance_writelock *m, model_group_instance_writelock *grp )
    {
        return this->t->genGroup( g, this, m, grp );
    }

};
