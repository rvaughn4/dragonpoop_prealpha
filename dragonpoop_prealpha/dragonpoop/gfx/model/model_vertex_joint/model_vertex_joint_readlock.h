
#ifndef dragonpoop_model_vertex_joint_readlock_h
#define dragonpoop_model_vertex_joint_readlock_h

#include "../model_component/model_component_readlock.h"

namespace dragonpoop
{
    class model_vertex_joint;
    class model_vertex_joint_ref;
    class model_joint_ref;
    class model_vertex_ref;

    class model_vertex_joint_readlock : public model_component_readlock
    {

    private:

        model_vertex_joint *t;

    protected:

        //ctor
        model_vertex_joint_readlock( model_vertex_joint *t, dpmutex_readlock *l );
        //dtor
        virtual ~model_vertex_joint_readlock( void );

    public:

        //returns joint id
        dpid getJointId( void );
        //returns joint
        model_joint_ref *getJoint( void );
        //returns vertex id
        dpid getVertexId( void );
        //returns vertex
        model_vertex_ref *getVertex( void );
        //returns weight
        float getWeight( void );

        friend class model_vertex_joint;
    };
    
};

#endif