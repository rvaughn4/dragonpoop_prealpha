
#include "model_instance_readlock.h"
#include "model_instance.h"

namespace dragonpoop
{

    //ctor
    model_instance_readlock::model_instance_readlock( model_instance *t, dpmutex_readlock *l ) : model_component_readlock( t, l )
    {
        this->t = t;
    }

    //dtor
    model_instance_readlock::~model_instance_readlock( void )
    {

    }

};
