
#ifndef dragonpoop_model_vertex_instance_writelock_h
#define dragonpoop_model_vertex_instance_writelock_h

#include "../model_component/model_component_writelock.h"

namespace dragonpoop
{

    class model_vertex_instance;
    class model_vertex_instance_ref;
    class dpvertex;
    class model_writelock;

    class model_vertex_instance_writelock : public model_component_writelock
    {

    private:

        model_vertex_instance *t;

    protected:

        //ctor
        model_vertex_instance_writelock( model_vertex_instance *t, dpmutex_writelock *l );
        //dtor
        virtual ~model_vertex_instance_writelock( void );

    public:

        //return instance id
        dpid getInstanceId( void );
        //return vertex id
        dpid getVertexId( void );
        //get vertex data
        void getVertex( model_writelock *ml, dpvertex *v );
        //sync vertex
        void sync( model_writelock *ml );

        friend class model_vertex_instance;
    };
    
};

#endif