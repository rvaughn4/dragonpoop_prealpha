
#ifndef dragonpoop_openglx_1o5_renderer_model_group_instance_readlock_h
#define dragonpoop_openglx_1o5_renderer_model_group_instance_readlock_h

#include "../../renderer_model_group_instance/renderer_model_group_instance_readlock.h"
#include "openglx_1o5_renderer_model_group_instance.h"

namespace dragonpoop
{

    class openglx_1o5_renderer_model_group_instance_readlock : public renderer_model_group_instance_readlock
    {

    private:

        openglx_1o5_renderer_model_group_instance *t;

    protected:

        //ctor
        openglx_1o5_renderer_model_group_instance_readlock( openglx_1o5_renderer_model_group_instance *t, dpmutex_readlock *l );
        //dtor
        virtual ~openglx_1o5_renderer_model_group_instance_readlock( void );

    public:

        friend class openglx_1o5_renderer_model_group_instance;
    };
    
};

#endif