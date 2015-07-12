
#ifndef dragonpoop_renderer_model_group_instance_h
#define dragonpoop_renderer_model_group_instance_h

#include "../../core/shared_obj/shared_obj.h"
#include "../../core/dpid/dpid.h"

namespace dragonpoop
{

    class core;
    class gfx_writelock;
    class gfx_ref;
    class dpthread_lock;
    class renderer_model_group_instance_ref;
    class renderer_model_group_instance_readlock;
    class renderer_model_group_instance_writelock;
    class renderer_ref;
    class renderer_writelock;

    class renderer_model_group_instance : public shared_obj
    {

    private:

        core *c;
        gfx_ref *g;
        dpid id, instance_id, parent_id;
        bool bAlive;
        renderer_ref *r;

    protected:

        //generate read lock
        virtual shared_obj_readlock *genReadLock( shared_obj *p, dpmutex_readlock *l );
        //generate write lock
        virtual shared_obj_writelock *genWriteLock( shared_obj *p, dpmutex_writelock *l );
        //generate ref
        virtual shared_obj_ref *genRef( shared_obj *p, std::shared_ptr<shared_obj_refkernal> *k );
        //get id
        dpid getId( void );
        //kill model
        void kill( void );
        //run model
        void run( dpthread_lock *thd, renderer_model_group_instance_writelock *m );
        //return instance id
        dpid getInstanceId( void );

    public:

        //ctor
        renderer_model_group_instance( gfx_writelock *g, renderer_writelock *r, dpid id, dpid instance_id );
        //dtor
        virtual ~renderer_model_group_instance( void );
        //return core
        core *getCore( void );
        //returns true if alive
        bool isAlive( void );

        friend class renderer_model_group_instance_readlock;
        friend class renderer_model_group_instance_writelock;
    };
    
};

#endif