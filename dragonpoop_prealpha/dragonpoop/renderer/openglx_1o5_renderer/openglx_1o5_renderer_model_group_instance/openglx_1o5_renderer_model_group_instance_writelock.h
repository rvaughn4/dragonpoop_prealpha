
#ifndef dragonpoop_openglx_1o5_renderer_model_group_instance_writelock_h
#define dragonpoop_openglx_1o5_renderer_model_group_instance_writelock_h

#include "../../renderer_model_group_instance/renderer_model_group_instance_writelock.h"
#include "openglx_1o5_renderer_model_group_instance.h"

namespace dragonpoop
{

    class openglx_1o5_renderer_model_group_instance_writelock : public renderer_model_group_instance_writelock
    {

    private:

        openglx_1o5_renderer_model_group_instance *t;

    protected:

        //ctor
        openglx_1o5_renderer_model_group_instance_writelock( openglx_1o5_renderer_model_group_instance *t, dpmutex_writelock *l );
        //dtor
        virtual ~openglx_1o5_renderer_model_group_instance_writelock( void );

    public:

        //return diffuse texture
        unsigned int getDiffuseTex( void );
        //return alpha texture
        unsigned int getAlphaTex( void );

        friend class openglx_1o5_renderer_model_group_instance;
    };
    
};

#endif