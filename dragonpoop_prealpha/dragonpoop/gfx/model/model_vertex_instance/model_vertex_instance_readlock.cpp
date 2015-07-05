
#include "model_vertex_instance_readlock.h"
#include "model_vertex_instance.h"

namespace dragonpoop
{

    //ctor
    model_vertex_instance_readlock::model_vertex_instance_readlock( model_vertex_instance *t, dpmutex_readlock *l ) : model_component_readlock( t, l )
    {
        this->t = t;
    }

    //dtor
    model_vertex_instance_readlock::~model_vertex_instance_readlock( void )
    {

    }
    
};
