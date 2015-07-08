
#ifndef dragonpoop_model_joint_instance_ref_h
#define dragonpoop_model_joint_instance_ref_h

#include "../model_component/model_component_ref.h"

namespace dragonpoop
{

    class model_joint_instance;

    class model_joint_instance_ref : public model_component_ref
    {

    private:

        model_joint_instance *t;

    protected:

        //ctor
        model_joint_instance_ref( model_joint_instance *p, std::shared_ptr<shared_obj_refkernal> *k );

    public:

        //dtor
        virtual ~model_joint_instance_ref( void );

        friend class model_joint_instance;
    };
    
};

#endif