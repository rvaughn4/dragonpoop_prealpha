
#include "model_joint_ref.h"
#include "model_joint.h"

namespace dragonpoop
{

    //ctor
    model_joint_ref::model_joint_ref( model_joint *p, std::shared_ptr<shared_obj_refkernal> *k ) : model_component_ref( p, k )
    {
        this->t = p;
    }

    //dtor
    model_joint_ref::~model_joint_ref( void )
    {

    }
    
};
