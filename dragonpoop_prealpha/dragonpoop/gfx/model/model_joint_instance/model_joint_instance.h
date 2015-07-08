
#ifndef dragonpoop_model_joint_instance_h
#define dragonpoop_model_joint_instance_h

#include "../model_component/model_component_type.h"
#include "../model_component/model_component.h"

namespace dragonpoop
{

    class model_joint_instance_ref;
    class model_joint_instance_readlock;
    class model_joint_instance_writelock;

    class model_joint_instance : public model_component
    {

    private:

        dpid instance_id, joint_id;

    protected:

        //generate read lock
        virtual shared_obj_readlock *genReadLock( shared_obj *p, dpmutex_readlock *l );
        //generate write lock
        virtual shared_obj_writelock *genWriteLock( shared_obj *p, dpmutex_writelock *l );
        //generate ref
        virtual shared_obj_ref *genRef( shared_obj *p, std::shared_ptr<shared_obj_refkernal> *k );
        //do background processing
        virtual void onRun( dpthread_lock *thd, gfx_writelock *g, model_writelock *m, model_component_writelock *l );
        //return instance id
        dpid getInstanceId( void );
        //return joint id
        dpid getJointId( void );

    public:

        //ctor
        model_joint_instance( model_writelock *ml, dpid id, dpid instance_id, dpid joint_id );
        //dtor
        virtual ~model_joint_instance( void );

        friend class model_joint_instance_readlock;
        friend class model_joint_instance_writelock;
    };
    
};

#endif
