
#ifndef dragonpoop_model_animation_frame_ref_h
#define dragonpoop_model_animation_frame_ref_h

#include "../model_component/model_component_ref.h"

namespace dragonpoop
{

    class model_animation_frame;

    class model_animation_frame_ref : public model_component_ref
    {

    private:

        model_animation_frame *t;

    protected:

        //ctor
        model_animation_frame_ref( model_animation_frame *p, std::shared_ptr<shared_obj_refkernal> *k );

    public:

        //dtor
        virtual ~model_animation_frame_ref( void );

        friend class model_animation_frame;
    };
    
};

#endif