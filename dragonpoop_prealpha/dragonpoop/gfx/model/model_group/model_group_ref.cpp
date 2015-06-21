
#include "model_group_ref.h"
#include "model_group.h"

namespace dragonpoop
{

    //ctor
    model_group_ref::model_group_ref( model_group *p, std::shared_ptr<shared_obj_refkernal> *k ) : model_component_ref( p, k )
    {
        this->t = p;
    }

    //dtor
    model_group_ref::~model_group_ref( void )
    {

    }

};
