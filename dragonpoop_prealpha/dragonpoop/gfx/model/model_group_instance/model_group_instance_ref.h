
#ifndef dragonpoop_model_group_instance_ref_h
#define dragonpoop_model_group_instance_ref_h

#include "../model_component/model_component_ref.h"

namespace dragonpoop
{

    class model_group_instance;

    class model_group_instance_ref : public model_component_ref
    {

    private:

        model_group_instance *t;

    protected:

        //ctor
        model_group_instance_ref( model_group_instance *p, std::shared_ptr<shared_obj_refkernal> *k );

    public:

        //dtor
        virtual ~model_group_instance_ref( void );

        friend class model_group_instance;
    };
    
};

#endif