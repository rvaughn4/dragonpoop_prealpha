
#include "openglx_1o5_renderer_model_group_instance_writelock.h"

namespace dragonpoop
{

    //ctor
    openglx_1o5_renderer_model_group_instance_writelock::openglx_1o5_renderer_model_group_instance_writelock( openglx_1o5_renderer_model_group_instance *t, dpmutex_writelock *l ) : renderer_model_group_instance_writelock( t, l )
    {
        this->t = t;
    }

    //dtor
    openglx_1o5_renderer_model_group_instance_writelock::~openglx_1o5_renderer_model_group_instance_writelock( void )
    {

    }

    //return diffuse texture
    unsigned int openglx_1o5_renderer_model_group_instance_writelock::getDiffuseTex( void )
    {
        return this->t->getDiffuseTex();
    }

    //return alpha texture
    unsigned int openglx_1o5_renderer_model_group_instance_writelock::getAlphaTex( void )
    {
        return this->t->getAlphaTex();
    }

};
