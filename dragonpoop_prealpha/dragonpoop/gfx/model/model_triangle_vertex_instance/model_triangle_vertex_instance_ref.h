
#ifndef dragonpoop_model_triangle_vertex_instance_ref_h
#define dragonpoop_model_triangle_vertex_instance_ref_h

#include "../model_component/model_component_ref.h"

namespace dragonpoop
{

    class model_triangle_vertex_instance;

    class model_triangle_vertex_instance_ref : public model_component_ref
    {

    private:

        model_triangle_vertex_instance *t;

    protected:

        //ctor
        model_triangle_vertex_instance_ref( model_triangle_vertex_instance *p, std::shared_ptr<shared_obj_refkernal> *k );

    public:

        //dtor
        virtual ~model_triangle_vertex_instance_ref( void );

        friend class model_triangle_vertex_instance;
    };
    
};

#endif