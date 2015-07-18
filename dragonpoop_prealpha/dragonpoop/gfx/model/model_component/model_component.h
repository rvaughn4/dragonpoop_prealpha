
#ifndef dragonpoop_model_component_h
#define dragonpoop_model_component_h

#include "../../../core/shared_obj/shared_obj.h"
#include "../../../core/shared_obj/shared_obj_guard.h"
#include "../../../core/dpid/dpid.h"
#include <string>
#include <atomic>

namespace dragonpoop
{

    class core;
    class dpthread_lock;
    class model_writelock;
    class model_component_writelock;
    class gfx_writelock;
    class model_ref;

    class model_component : public shared_obj
    {

    private:

        core *c;
        model_ref *m;
        dpid id;
        bool bAlive;
        uint16_t ctype;
        std::atomic<uint64_t> run_wait, last_run;
        std::string scomment;

    protected:

        //generate read lock
        virtual shared_obj_readlock *genReadLock( shared_obj *p, dpmutex_readlock *l );
        //generate write lock
        virtual shared_obj_writelock *genWriteLock( shared_obj *p, dpmutex_writelock *l );
        //generate ref
        virtual shared_obj_ref *genRef( shared_obj *p, std::shared_ptr<shared_obj_refkernal> *k );
        //get id
        dpid getId( void );
        //get type
        uint16_t getType( void );
        //kill model
        void kill( void );
        //run model
        void run( dpthread_lock *thd, gfx_writelock *g, model_writelock *m, model_component_writelock *l );
        //do background processing
        virtual void onRun( dpthread_lock *thd, gfx_writelock *g, model_writelock *m, model_component_writelock *l );
        //return model
        model_ref *getModel( void );
        //get comment
        void getComment( std::string *s );
        //set comment
        void setComment( std::string *s );
        //add comment
        void addComment( std::string *s );

    public:

        //ctor
        model_component( model_writelock *ml, dpid id, uint16_t ctype, uint64_t run_wait );
        //dtor
        virtual ~model_component( void );
        //return core
        core *getCore( void );
        //returns true if alive
        bool isAlive( void );

        friend class model_component_readlock;
        friend class model_component_writelock;
    };
    
};

#endif
