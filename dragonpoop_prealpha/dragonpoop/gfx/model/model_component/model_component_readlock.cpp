
#include "model_component_readlock.h"
#include "model_component.h"

namespace dragonpoop
{

    //ctor
    model_component_readlock::model_component_readlock( model_component *t, dpmutex_readlock *l ) : shared_obj_readlock( t, l )
    {
        this->t = t;
    }

    //dtor
    model_component_readlock::~model_component_readlock( void )
    {

    }

    //return core
    core *model_component_readlock::getCore( void )
    {
        return this->t->getCore();
    }

    //get id
    dpid model_component_readlock::getId( void )
    {
        return this->t->getId();
    }

    //get type
    uint16_t model_component_readlock::getType( void )
    {
        return this->t->getType();
    }

    //returns true if alive
    bool model_component_readlock::isAlive( void )
    {
        return this->t->isAlive();
    }

    //return model
    model_ref *model_component_readlock::getModel( void )
    {
        return this->t->getModel();
    }

};
