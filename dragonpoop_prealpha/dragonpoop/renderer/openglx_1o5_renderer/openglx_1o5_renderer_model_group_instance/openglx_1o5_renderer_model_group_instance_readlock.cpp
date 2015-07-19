
#include "openglx_1o5_renderer_model_group_instance_readlock.h"

namespace dragonpoop
{

    //ctor
    openglx_1o5_renderer_model_group_instance_readlock::openglx_1o5_renderer_model_group_instance_readlock( openglx_1o5_renderer_model_group_instance *t, dpmutex_readlock *l ) : renderer_model_group_instance_readlock( t, l )
    {
        this->t = t;
    }

    //dtor
    openglx_1o5_renderer_model_group_instance_readlock::~openglx_1o5_renderer_model_group_instance_readlock( void )
    {

    }

    //return diffuse texture
    unsigned int openglx_1o5_renderer_model_group_instance_readlock::getDiffuseTex( void )
    {
        return this->t->getDiffuseTex();
    }

    //return alpha texture
    unsigned int openglx_1o5_renderer_model_group_instance_readlock::getAlphaTex( void )
    {
        return this->t->getAlphaTex();
    }

};
