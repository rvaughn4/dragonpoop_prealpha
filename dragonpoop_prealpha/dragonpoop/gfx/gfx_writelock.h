
#ifndef dragonpoop_gfx_writelock_h
#define dragonpoop_gfx_writelock_h

#include "../core/shared_obj/shared_obj_writelock.h"
#include "../core/dpid/dpid.h"
#include <list>

namespace dragonpoop
{
    class gfx;
    class core;
    class dpthread_lock;
    class model_ref;
    class model_instance_ref;

    class gfx_writelock : public shared_obj_writelock
    {

    private:

        gfx *t;

    protected:

        //ctor
        gfx_writelock( gfx *t, dpmutex_writelock *l );
        //dtor
        virtual ~gfx_writelock( void );

    public:

        //returns true if running
        bool isRunning( void );
        //return core
        core *getCore( void );
        //stop gfx task
        void kill( void );
        //run gfx from task
        void run( dpthread_lock *thd );
        //find model by id
        model_ref *findModel( dpid id );
        //find model by name
        model_ref *findModel( const char *c );
        //create model
        model_ref *createModel( dpthread_lock *thd );
        //create model having name
        model_ref *createModel( dpthread_lock *thd, const char *cname );
        //create model having id
        model_ref *createModel( dpthread_lock *thd, dpid id );
        //create model having id and name
        model_ref *createModel( dpthread_lock *thd, dpid id, const char *cname );
        //get model instances
        unsigned int getInstances( std::list<model_instance_ref *> *l );
        //release list returned by getInstances()
        void releaseGetInstances( std::list<model_instance_ref *> *l );

        friend class gfx;
    };
    
};

#endif