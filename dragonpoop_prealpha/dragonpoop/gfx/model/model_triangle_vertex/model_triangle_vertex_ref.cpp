
#include "model_triangle_vertex_ref.h"
#include "model_triangle_vertex.h"

namespace dragonpoop
{

    //ctor
    model_triangle_vertex_ref::model_triangle_vertex_ref( model_triangle_vertex *p, std::shared_ptr<shared_obj_refkernal> *k ) : model_component_ref( p, k )
    {
        this->t = p;
    }

    //dtor
    model_triangle_vertex_ref::~model_triangle_vertex_ref( void )
    {

    }

};
