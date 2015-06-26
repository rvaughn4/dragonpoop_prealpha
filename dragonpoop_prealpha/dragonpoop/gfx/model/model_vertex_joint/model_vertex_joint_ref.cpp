
#include "model_vertex_joint_ref.h"
#include "model_vertex_joint.h"

namespace dragonpoop
{

    //ctor
    model_vertex_joint_ref::model_vertex_joint_ref( model_vertex_joint *p, std::shared_ptr<shared_obj_refkernal> *k ) : model_component_ref( p, k )
    {
        this->t = p;
    }

    //dtor
    model_vertex_joint_ref::~model_vertex_joint_ref( void )
    {

    }
    
};
