
#ifndef dragonpoop_renderer_model_instance_writelock_h
#define dragonpoop_renderer_model_instance_writelock_h

#include "../../core/shared_obj/shared_obj_writelock.h"
#include "renderer_model_instance.h"

namespace dragonpoop
{

    class renderer_model_instance_writelock : public shared_obj_writelock
    {

    private:

        renderer_model_instance *t;

    protected:

        //ctor
        renderer_model_instance_writelock( renderer_model_instance *t, dpmutex_writelock *l );
        //dtor
        virtual ~renderer_model_instance_writelock( void );

    public:

        //return core
        core *getCore( void );
        //returns true if alive
        bool isAlive( void );
        //get id
        dpid getId( void );
        //kill model
        void kill( void );
        //run model
        void run( dpthread_lock *thd, renderer_writelock *r );
        //render model
        void render( dpthread_lock *thd, renderer_writelock *r );
        //forces an update to happen next run cycle
        void update( void );

        friend class renderer_model_instance;
    };
    
};

#endif