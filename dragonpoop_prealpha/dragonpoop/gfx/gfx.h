
#ifndef dragonpoop_gfx_h
#define dragonpoop_gfx_h

#include "../core/shared_obj/shared_obj.h"
#include "../core/bytetree/dpid_bytetree.h"

namespace dragonpoop
{

    class dptaskpool_writelock;
    class dptask;
    class gfx_task;
    class dpthread_lock;
    class core;
    class renderer;
    class model;
    class gfx_writelock;
    class model_ref;
    class model_instance_ref;

    class gfx : public shared_obj
    {

    private:

        dptask *tsk;
        gfx_task *gtsk;
        core *c;
        renderer *r;

        //models
        std::list<model *> models;
        dpid_bytetree model_tree;

    protected:

        //generate read lock
        virtual shared_obj_readlock *genReadLock( shared_obj *p, dpmutex_readlock *l );
        //generate write lock
        virtual shared_obj_writelock *genWriteLock( shared_obj *p, dpmutex_writelock *l );
        //generate ref
        virtual shared_obj_ref *genRef( shared_obj *p, std::shared_ptr<shared_obj_refkernal> *k );
        //stop gfx task
        void kill( void );
        //run gfx from task
        void run( dpthread_lock *thd, gfx_writelock *g );

        //run all models
        void runModels( dpthread_lock *thd, gfx_writelock *g );
        //delete all models
        void deleteModels( void );
        //find model by id
        model_ref *findModel( dpid id );
        //find model by name
        model_ref *findModel( const char *c );
        //create model
        model_ref *createModel( dpthread_lock *thd, gfx_writelock *g );
        //create model having name
        model_ref *createModel( dpthread_lock *thd, gfx_writelock *g, const char *cname );
        //create model having id
        model_ref *createModel( dpthread_lock *thd, gfx_writelock *g, dpid id );
        //create model having id and name
        model_ref *createModel( dpthread_lock *thd, gfx_writelock *g, dpid id, const char *cname );
        //get model instances
        unsigned int getInstances( std::list<model_instance_ref *> *l );

    public:

        //ctor
        gfx( core *c, dptaskpool_writelock *tp );
        //dtor
        virtual ~gfx( void );
        //returns true if running
        bool isRunning( void );
        //return core
        core *getCore( void );
        //release list returned by getInstances()
        static void releaseGetInstances( std::list<model_instance_ref *> *l );

        friend class gfx_readlock;
        friend class gfx_writelock;
    };
    
};

#endif