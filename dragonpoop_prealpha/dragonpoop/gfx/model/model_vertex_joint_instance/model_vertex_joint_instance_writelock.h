
#ifndef dragonpoop_model_vertex_joint_instance_writelock_h
#define dragonpoop_model_vertex_joint_instance_writelock_h

#include "../model_component/model_component_writelock.h"

namespace dragonpoop
{

    class model_vertex_joint_instance;
    class model_vertex_joint_instance_ref;

    class model_vertex_joint_instance_writelock : public model_component_writelock
    {

    private:

        model_vertex_joint_instance *t;

    protected:

        //ctor
        model_vertex_joint_instance_writelock( model_vertex_joint_instance *t, dpmutex_writelock *l );
        //dtor
        virtual ~model_vertex_joint_instance_writelock( void );

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