
#ifndef dragonpoop_model_vertex_joint_instance_readlock_h
#define dragonpoop_model_vertex_joint_instance_readlock_h

#include "../model_component/model_component_readlock.h"

namespace dragonpoop
{

    class model_vertex_joint_instance;
    class model_vertex_joint_instance_ref;

    class model_vertex_joint_instance_readlock : public model_component_readlock
    {

    private:

        model_vertex_joint_instance *t;

    protected:

        //ctor
        model_vertex_joint_instance_readlock( model_vertex_joint_instance *t, dpmutex_readlock *l );
        //dtor
        virtual ~model_vertex_joint_instance_readlock( void );

    public:

        //return instance id
        dpid getInstanceId( void );
        //return vertex_joint id
        dpid getVertexJointId( void );
        //return joint id
        dpid getJointId( void );
        //return vertex id
        dpid getVertexId( void );

        friend class model_vertex_joint_instance;
    };
    
};

#endif