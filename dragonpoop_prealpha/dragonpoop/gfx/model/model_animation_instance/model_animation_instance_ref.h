
#ifndef dragonpoop_model_animation_instance_ref_h
#define dragonpoop_model_animation_instance_ref_h

#include "../model_component/model_component_ref.h"

namespace dragonpoop
{

    class model_animation_instance;

    class model_animation_instance_ref : public model_component_ref
    {

    private:

        model_animation_instance *t;

    protected:

        //ctor
        model_animation_instance_ref( model_animation_instance *p, std::shared_ptr<shared_obj_refkernal> *k );

    public:

        //dtor
        virtual ~model_animation_instance_ref( void );

        friend class model_animation_instance;
    };
    
};

#endif