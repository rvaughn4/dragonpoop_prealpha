
#ifndef dragonpoop_model_component_writelock_h
#define dragonpoop_model_component_writelock_h

#include "../../../core/shared_obj/shared_obj_writelock.h"
#include "../../../core/dpid/dpid.h"

namespace dragonpoop
{
    class model_component;
    class core;
    class dpthread_lock;
    class gfx_writelock;
    class model_writelock;
    class model_ref;

    class model_component_writelock : public shared_obj_writelock
    {

    private:

        model_component *t;

    protected:

        //ctor
        model_component_writelock( model_component *t, dpmutex_writelock *l );
        //dtor
        virtual ~model_component_writelock( void );

    public:

        //return core
        core *getCore( void );
        //get id
        dpid getId( void );
        //get type
        uint16_t getType( void );
        //returns true if alive
        bool isAlive( void );
        //kill model
        void kill( void );
        //run model
        void run( dpthread_lock *thd, gfx_writelock *g, model_writelock *m );
        //return model
        model_ref *getModel( void );

        friend class model_component;
    };
    
};

#endif