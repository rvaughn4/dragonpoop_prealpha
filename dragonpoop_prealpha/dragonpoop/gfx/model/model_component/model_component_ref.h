
#ifndef dragonpoop_model_component_ref_h
#define dragonpoop_model_component_ref_h

#include "../../../core/shared_obj/shared_obj_ref.h"

namespace dragonpoop
{

    class model_component;

    class model_component_ref : public shared_obj_ref
    {

    private:

        model_component *t;

    protected:

        //ctor
        model_component_ref( model_component *p, std::shared_ptr<shared_obj_refkernal> *k );

    public:

        //dtor
        virtual ~model_component_ref( void );
        
        friend class model_component;
    };
    
};

#endif