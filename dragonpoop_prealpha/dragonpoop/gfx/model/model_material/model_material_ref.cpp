
#include "model_material_ref.h"
#include "model_material.h"

namespace dragonpoop
{

    //ctor
    model_material_ref::model_material_ref( model_material *p, std::shared_ptr<shared_obj_refkernal> *k ) : model_component_ref( p, k )
    {
        this->t = p;
    }

    //dtor
    model_material_ref::~model_material_ref( void )
    {

    }
    
};
