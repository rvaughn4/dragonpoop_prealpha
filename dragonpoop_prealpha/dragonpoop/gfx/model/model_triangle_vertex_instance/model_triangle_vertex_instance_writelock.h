
#ifndef dragonpoop_model_triangle_vertex_instance_writelock_h
#define dragonpoop_model_triangle_vertex_instance_writelock_h

#include "../model_component/model_component_writelock.h"

namespace dragonpoop
{

    class model_triangle_vertex_instance;
    class model_triangle_vertex_instance_ref;

    class model_triangle_vertex_instance_writelock : public model_component_writelock
    {

    private:

        model_triangle_vertex_instance *t;

    protected:

        //ctor
        model_triangle_vertex_instance_writelock( model_triangle_vertex_instance *t, dpmutex_writelock *l );
        //dtor
        virtual ~model_triangle_vertex_instance_writelock( void );

    public:

        //return instance id
        dpid getInstanceId( void );

        friend class model_triangle_vertex_instance;
    };
    
};

#endif