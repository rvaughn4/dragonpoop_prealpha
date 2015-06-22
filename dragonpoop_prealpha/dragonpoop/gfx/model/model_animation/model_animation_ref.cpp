
#include "model_animation_ref.h"
#include "model_animation.h"

namespace dragonpoop
{

    //ctor
    model_animation_ref::model_animation_ref( model_animation *p, std::shared_ptr<shared_obj_refkernal> *k ) : model_component_ref( p, k )
    {
        this->t = p;
    }

    //dtor
    model_animation_ref::~model_animation_ref( void )
    {

    }
    
};
