
#ifndef dragonpoop_renderer_model_instance_readlock_h
#define dragonpoop_renderer_model_instance_readlock_h

#include "../../core/shared_obj/shared_obj_readlock.h"
#include "renderer_model_group_instance.h"

namespace dragonpoop
{

    class renderer_model_group_instance_readlock : public shared_obj_readlock
    {

    private:

        renderer_model_group_instance *t;

    protected:

        //ctor
        renderer_model_group_instance_readlock( renderer_model_group_instance *t, dpmutex_readlock *l );
        //dtor
        virtual ~renderer_model_group_instance_readlock( void );

    public:

        //return core
        core *getCore( void );
        //returns true if alive
        bool isAlive( void );
        //get id
        dpid getId( void );
        //return instance id
        dpid getInstanceId( void );

        friend class renderer_model_group_instance;
    };
    
};

#endif