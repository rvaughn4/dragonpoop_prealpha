
#include "renderer_model_group_instance_readlock.h"
#include "renderer_model_group_instance.h"

namespace dragonpoop
{

    //ctor
    renderer_model_group_instance_readlock::renderer_model_group_instance_readlock( renderer_model_group_instance *t, dpmutex_readlock *l ) : shared_obj_readlock( t, l )
    {
        this->t = t;
    }

    //dtor
    renderer_model_group_instance_readlock::~renderer_model_group_instance_readlock( void )
    {

    }

    //return core
    core *renderer_model_group_instance_readlock::getCore( void )
    {
        return this->t->getCore();
    }

    //returns true if alive
    bool renderer_model_group_instance_readlock::isAlive( void )
    {
        return this->t->isAlive();
    }

    //get id
    dpid renderer_model_group_instance_readlock::getId( void )
    {
        return this->t->getId();
    }

    //return instance id
    dpid renderer_model_group_instance_readlock::getInstanceId( void )
    {
        return this->t->getInstanceId();
    }

    //render group
    void renderer_model_group_instance_readlock::render( dpthread_lock *thd, renderer_model_instance_readlock *m, renderer_writelock *r )
    {
        this->t->render( thd, m, this, r );
    }

    //returns pointer to vertex buffer
    dpvertexindex_buffer *renderer_model_group_instance_readlock::getBuffer( void )
    {
        return this->t->getBuffer();
    }

};
