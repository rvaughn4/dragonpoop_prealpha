
#ifndef dragonpoop_model_triangle_vertex_ref_h
#define dragonpoop_model_triangle_vertex_ref_h

#include "../model_component/model_component_ref.h"

namespace dragonpoop
{

    class model_triangle_vertex;

    class model_triangle_vertex_ref : public model_component_ref
    {

    private:

        model_triangle_vertex *t;

    protected:

        //ctor
        model_triangle_vertex_ref( model_triangle_vertex *p, std::shared_ptr<shared_obj_refkernal> *k );

    public:

        //dtor
        virtual ~model_triangle_vertex_ref( void );

        friend class model_triangle_vertex;
    };
    
};

#endif