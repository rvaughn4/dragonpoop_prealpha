
#include "renderer_model_instance_readlock.h"

namespace dragonpoop
{

    //ctor
    renderer_model_instance_readlock::renderer_model_instance_readlock( renderer_model_instance *t, dpmutex_readlock *l ) : shared_obj_readlock( t, l )
    {
        this->t = t;
    }

    //dtor
    renderer_model_instance_readlock::~renderer_model_instance_readlock( void )
    {

    }

    //return core
    core *renderer_model_instance_readlock::getCore( void )
    {
        return this->t->getCore();
    }

    //returns true if alive
    bool renderer_model_instance_readlock::isAlive( void )
    {
        return this->t->isAlive();
    }

    //get id
    dpid renderer_model_instance_readlock::getId( void )
    {
        return this->t->getId();
    }

};
