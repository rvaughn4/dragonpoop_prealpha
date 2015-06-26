
#ifndef dragonpoop_model_vertex_joint_ref_h
#define dragonpoop_model_vertex_joint_ref_h

#include "../model_component/model_component_ref.h"

namespace dragonpoop
{

    class model_vertex_joint;

    class model_vertex_joint_ref : public model_component_ref
    {

    private:

        model_vertex_joint *t;

    protected:

        //ctor
        model_vertex_joint_ref( model_vertex_joint *p, std::shared_ptr<shared_obj_refkernal> *k );

    public:

        //dtor
        virtual ~model_vertex_joint_ref( void );

        friend class model_vertex_joint;
    };
    
};

#endif