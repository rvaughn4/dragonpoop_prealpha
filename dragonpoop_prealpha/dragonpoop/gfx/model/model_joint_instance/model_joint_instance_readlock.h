
#ifndef dragonpoop_model_joint_instance_readlock_h
#define dragonpoop_model_joint_instance_readlock_h

#include "../model_component/model_component_readlock.h"

namespace dragonpoop
{

    class model_joint_instance;
    class model_joint_instance_ref;
    struct dpxyzw;

    class model_joint_instance_readlock : public model_component_readlock
    {

    private:

        model_joint_instance *t;

    protected:

        //ctor
        model_joint_instance_readlock( model_joint_instance *t, dpmutex_readlock *l );
        //dtor
        virtual ~model_joint_instance_readlock( void );

    public:

        //return instance id
        dpid getInstanceId( void );
        //return joint id
        dpid getJointId( void );
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