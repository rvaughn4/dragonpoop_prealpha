
#include "model_vertex_joint_instance_ref.h"
#include "model_vertex_joint_instance.h"

namespace dragonpoop
{

    //ctor
    model_vertex_joint_instance_ref::model_vertex_joint_instance_ref( model_vertex_joint_instance *p, std::shared_ptr<shared_obj_refkernal> *k ) : model_component_ref( p, k )
    {
        this->t = p;
    }

    //dtor
    model_vertex_joint_instance_ref::~model_vertex_joint_instance_ref( void )
    {

    }
    
};
