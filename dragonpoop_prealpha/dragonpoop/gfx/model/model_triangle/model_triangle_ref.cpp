
#include "model_triangle_ref.h"
#include "model_triangle.h"

namespace dragonpoop
{

    //ctor
    model_triangle_ref::model_triangle_ref( model_triangle *p, std::shared_ptr<shared_obj_refkernal> *k ) : model_component_ref( p, k )
    {
        this->t = p;
    }

    //dtor
    model_triangle_ref::~model_triangle_ref( void )
    {

    }
    
};
