
#ifndef dragonpoop_model_joint_instance_writelock_h
#define dragonpoop_model_joint_instance_writelock_h

#include "../model_component/model_component_writelock.h"

namespace dragonpoop
{

    class model_joint_instance;
    class model_joint_instance_ref;
    struct dpxyzw;
    class dpthread_lock;
    class model_writelock;

    class model_joint_instance_writelock : public model_component_writelock
    {

    private:

        model_joint_instance *t;

    protected:

        //ctor
        model_joint_instance_writelock( model_joint_instance *t, dpmutex_writelock *l );
        //dtor
        virtual ~model_joint_instance_writelock( void );

    public:

        //return instance id
        dpid getInstanceId( void );
        //return joint id
        dpid getJointId( void );
        //sync joint
        void sync( dpthread_lock *thd, model_writelock *ml );
        //get translation for this joint
        void getTranslation( dpxyzw *x );
        //get rotation for this joint
        void getRotation( dpxyzw *x );
        //get animation time for this joint
        uint64_t getTime( void );

        friend class model_joint_instance;
    };
    
};

#endif