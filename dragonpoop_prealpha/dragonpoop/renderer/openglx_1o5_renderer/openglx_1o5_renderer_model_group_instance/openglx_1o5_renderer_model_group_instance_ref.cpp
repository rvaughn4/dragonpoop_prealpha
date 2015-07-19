
#include "openglx_1o5_renderer_model_group_instance_ref.h"
#include "openglx_1o5_renderer_model_group_instance.h"

namespace dragonpoop
{

    //ctor
    openglx_1o5_renderer_model_group_instance_ref::openglx_1o5_renderer_model_group_instance_ref( openglx_1o5_renderer_model_group_instance *t, std::shared_ptr<shared_obj_refkernal> *k ) : renderer_model_group_instance_ref( t, k )
    {
        this->t = t;
    }

    //dtor
    openglx_1o5_renderer_model_group_instance_ref::~openglx_1o5_renderer_model_group_instance_ref( void )
    {

    }
    
};
