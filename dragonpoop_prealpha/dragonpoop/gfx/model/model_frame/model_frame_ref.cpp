
#include "model_frame_ref.h"
#include "model_frame.h"

namespace dragonpoop
{

    //ctor
    model_frame_ref::model_frame_ref( model_frame *p, std::shared_ptr<shared_obj_refkernal> *k ) : model_component_ref( p, k )
    {
        this->t = p;
    }

    //dtor
    model_frame_ref::~model_frame_ref( void )
    {

    }
    
};
