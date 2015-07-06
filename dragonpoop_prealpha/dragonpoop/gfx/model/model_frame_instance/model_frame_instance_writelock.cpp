
#include "model_frame_instance_writelock.h"
#include "model_frame_instance.h"

namespace dragonpoop
{

    //ctor
    model_frame_instance_writelock::model_frame_instance_writelock( model_frame_instance *t, dpmutex_writelock *l ) : model_component_writelock( t, l )
    {
        this->t = t;
    }

    //dtor
    model_frame_instance_writelock::~model_frame_instance_writelock( void )
    {

    }

    //return instance id
    dpid model_frame_instance_writelock::getInstanceId( void )
    {
        return this->t->getInstanceId();
    }

    //return frame id
    dpid model_frame_instance_writelock::getFrameId( void )
    {
        return this->t->getFrameId();
    }
    
};
