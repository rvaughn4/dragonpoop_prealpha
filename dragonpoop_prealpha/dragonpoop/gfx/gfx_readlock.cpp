
#include "gfx_readlock.h"
#include "gfx.h"

namespace dragonpoop
{

    //ctor
    gfx_readlock::gfx_readlock( gfx *t, dpmutex_readlock *l ) : shared_obj_readlock( t, l )
    {
        this->t = t;
    }

    //dtor
    gfx_readlock::~gfx_readlock( void )
    {

    }

    //returns true if running
    bool gfx_readlock::isRunning( void )
    {
        return this->t->isRunning();
    }

    //return core
    core *gfx_readlock::getCore( void )
    {
        return this->t->getCore();
    }

    //get model instances
    unsigned int gfx_readlock::getInstances( std::list<model_instance_ref *> *l )
    {
        return this->t->getInstances( l );
    }

    //release list returned by getInstances()
    void gfx_readlock::releaseGetInstances( std::list<model_instance_ref *> *l )
    {
        gfx::releaseGetInstances( l );
    }

};
