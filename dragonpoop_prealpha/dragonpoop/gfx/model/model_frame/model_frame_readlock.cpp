
#include "model_frame_readlock.h"
#include "model_frame.h"

namespace dragonpoop
{

    //ctor
    model_frame_readlock::model_frame_readlock( model_frame *t, dpmutex_readlock *l ) : model_component_readlock( t, l )
    {
        this->t = t;
    }

    //dtor
    model_frame_readlock::~model_frame_readlock( void )
    {

    }

    //get name
    void model_frame_readlock::getName( std::string *s )
    {
        this->t->getName( s );
    }

};
