
#include "renderer_model_group_instance_writelock.h"
#include "renderer_model_group_instance.h"

namespace dragonpoop
{

    //ctor
    renderer_model_group_instance_writelock::renderer_model_group_instance_writelock( renderer_model_group_instance *t, dpmutex_writelock *l ) : shared_obj_writelock( t, l )
    {
        this->t = t;
    }

    //dtor
    renderer_model_group_instance_writelock::~renderer_model_group_instance_writelock( void )
    {

    }

    //return core
    core *renderer_model_group_instance_writelock::getCore( void )
    {
        return this->t->getCore();
    }

    //returns true if alive
    bool renderer_model_group_instance_writelock::isAlive( void )
    {
        return this->t->isAlive();
    }

    //get id
    dpid renderer_model_group_instance_writelock::getId( void )
    {
        return this->t->getId();
    }

    //kill group
    void renderer_model_group_instance_writelock::kill( void )
    {
        this->t->kill();
    }

    //run group
    void renderer_model_group_instance_writelock::run( dpthread_lock *thd, renderer_model_instance_writelock *m, renderer_writelock *r )
    {
        this->t->run( thd, m, this, r );
    }

    //render group
    void renderer_model_group_instance_writelock::render( dpthread_lock *thd, renderer_model_instance_writelock *m, renderer_writelock *r )
    {
        this->t->render( thd, m, this, r );
    }

    //return instance id
    dpid renderer_model_group_instance_writelock::getInstanceId( void )
    {
        return this->t->getInstanceId();
    }

};
