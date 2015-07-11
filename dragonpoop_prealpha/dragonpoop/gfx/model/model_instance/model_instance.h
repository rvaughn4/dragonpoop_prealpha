
#ifndef dragonpoop_model_instance_h
#define dragonpoop_model_instance_h

#include "../model_component/model_component_type.h"
#include "../model_component/model_component.h"

namespace dragonpoop
{

    class model_instance_ref;
    class model_instance_readlock;
    class model_instance_writelock;
    class model_readlock;
    class model_group_instance_ref;

    class model_instance : public model_component
    {

    private:

    protected:

        //generate read lock
        virtual shared_obj_readlock *genReadLock( shared_obj *p, dpmutex_readlock *l );
        //generate write lock
        virtual shared_obj_writelock *genWriteLock( shared_obj *p, dpmutex_writelock *l );
        //generate ref
        virtual shared_obj_ref *genRef( shared_obj *p, std::shared_ptr<shared_obj_refkernal> *k );
        //do background processing
        virtual void onRun( dpthread_lock *thd, gfx_writelock *g, model_writelock *m, model_component_writelock *l );

        //create group instances
        void makeGroups( dpthread_lock *thd, model_writelock *ml );
        //destroy group instances
        void killGroups( void );
        //get group instances
        unsigned int getGroups( std::list<model_group_instance_ref *> *l );
        //get group instances by parent
        unsigned int getGroupsByParent( dpid parent_id, std::list<model_group_instance_ref *> *l );
        //release list returned by getGroups()
        static void releaseGetGroups( std::list<model_group_instance_ref *> *l );

    public:

        //ctor
        model_instance( dpthread_lock *thd, model_writelock *ml, dpid id );
        //dtor
        virtual ~model_instance( void );

        friend class model_instance_readlock;
        friend class model_instance_writelock;
    };
    
};

#endif
