
#include "renderer_model_instance_writelock.h"

namespace dragonpoop
{

    //ctor
    renderer_model_instance_writelock::renderer_model_instance_writelock( renderer_model_instance *t, dpmutex_writelock *l ) : shared_obj_writelock( t, l )
    {
        this->t = t;
    }

    //dtor
    renderer_model_instance_writelock::~renderer_model_instance_writelock( void )
    {

    }

    //return core
    core *renderer_model_instance_writelock::getCore( void )
    {
        return this->t->getCore();
    }

    //returns true if alive
    bool renderer_model_instance_writelock::isAlive( void )
    {
        return this->t->isAlive();
    }

    //get id
    dpid renderer_model_instance_writelock::getId( void )
    {
        return this->t->getId();
    }

    //kill model
    void renderer_model_instance_writelock::kill( void )
    {
        this->t->kill();
    }

    //run model
    void renderer_model_instance_writelock::run( dpthread_lock *thd )
    {
        this->t->run( thd, this );
    }

};
