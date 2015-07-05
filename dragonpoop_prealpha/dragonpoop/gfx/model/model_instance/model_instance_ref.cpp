
#include "model_instance_ref.h"
#include "model_instance.h"

namespace dragonpoop
{

    //ctor
    model_instance_ref::model_instance_ref( model_instance *p, std::shared_ptr<shared_obj_refkernal> *k ) : model_component_ref( p, k )
    {
        this->t = p;
    }

    //dtor
    model_instance_ref::~model_instance_ref( void )
    {

    }

};
