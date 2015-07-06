
#include "model_frame_instance_readlock.h"
#include "model_frame_instance.h"

namespace dragonpoop
{

    //ctor
    model_frame_instance_readlock::model_frame_instance_readlock( model_frame_instance *t, dpmutex_readlock *l ) : model_component_readlock( t, l )
    {
        this->t = t;
    }

    //dtor
    model_frame_instance_readlock::~model_frame_instance_readlock( void )
    {

    }

    //return instance id
    dpid model_frame_instance_readlock::getInstanceId( void )
    {
        return this->t->getInstanceId();
    }

    //return frame id
    dpid model_frame_instance_readlock::getFrameId( void )
    {
        return this->t->getFrameId();
    }
    
};
