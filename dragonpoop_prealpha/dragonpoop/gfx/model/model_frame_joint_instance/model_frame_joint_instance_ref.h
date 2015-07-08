
#ifndef dragonpoop_model_frame_joint_instance_ref_h
#define dragonpoop_model_frame_joint_instance_ref_h

#include "../model_component/model_component_ref.h"

namespace dragonpoop
{

    class model_frame_joint_instance;

    class model_frame_joint_instance_ref : public model_component_ref
    {

    private:

        model_frame_joint_instance *t;

    protected:

        //ctor
        model_frame_joint_instance_ref( model_frame_joint_instance *p, std::shared_ptr<shared_obj_refkernal> *k );

    public:

        //dtor
        virtual ~model_frame_joint_instance_ref( void );

        friend class model_frame_joint_instance;
    };
    
};

#endif