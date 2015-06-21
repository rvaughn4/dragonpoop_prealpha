
#ifndef dragonpoop_model_component_readlock_h
#define dragonpoop_model_component_readlock_h

#include "../../../core/shared_obj/shared_obj_readlock.h"
#include "../../../core/dpid/dpid.h"

namespace dragonpoop
{
    class model_component;
    class core;
    class model_ref;

    class model_component_readlock : public shared_obj_readlock
    {

    private:

        model_component *t;

    protected:

        //ctor
        model_component_readlock( model_component *t, dpmutex_readlock *l );
        //dtor
        virtual ~model_component_readlock( void );

    public:

        //return core
        core *getCore( void );
        //get id
        dpid getId( void );
        //get type
        uint16_t getType( void );
        //returns true if alive
        bool isAlive( void );
        //return model
        model_ref *getModel( void );

        friend class model_component;
    };
    
};

#endif