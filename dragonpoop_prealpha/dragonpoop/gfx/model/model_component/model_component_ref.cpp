
#include "model_component_ref.h"
#include "model_component.h"

namespace dragonpoop
{

    //ctor
    model_component_ref::model_component_ref( model_component *p, std::shared_ptr<shared_obj_refkernal> *k ) : shared_obj_ref( p, k )
    {
        this->t = p;
    }

    //dtor
    model_component_ref::~model_component_ref( void )
    {

    }

};
