
#ifndef dragonpoop_model_vertex_joint_writelock_h
#define dragonpoop_model_vertex_joint_writelock_h

#include "../model_component/model_component_writelock.h"

namespace dragonpoop
{
    class model_vertex_joint;
    class model_vertex_joint_ref;
    class model_joint_ref;
    class model_vertex_ref;

    class model_vertex_joint_writelock : public model_component_writelock
    {

    private:

        model_vertex_joint *t;

    protected:

        //ctor
        model_vertex_joint_writelock( model_vertex_joint *t, dpmutex_writelock *l );
        //dtor
        virtual ~model_vertex_joint_writelock( void );

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
        //sets weight
        void setWeight( float w );

        
        friend class model_vertex_joint;
    };
    
};

#endif