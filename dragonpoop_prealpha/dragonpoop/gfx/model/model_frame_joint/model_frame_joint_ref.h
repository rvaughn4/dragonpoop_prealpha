
#ifndef dragonpoop_model_frame_joint_ref_h
#define dragonpoop_model_frame_joint_ref_h

#include "../model_component/model_component_ref.h"

namespace dragonpoop
{

    class model_frame_joint;

    class model_frame_joint_ref : public model_component_ref
    {

    private:

        model_frame_joint *t;

    protected:

        //ctor
        model_frame_joint_ref( model_frame_joint *p, std::shared_ptr<shared_obj_refkernal> *k );

    public:

        //dtor
        virtual ~model_frame_joint_ref( void );

        friend class model_frame_joint;
    };
    
};

#endif