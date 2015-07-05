
#ifndef dragonpoop_model_triangle_instance_readlock_h
#define dragonpoop_model_triangle_instance_readlock_h

#include "../model_component/model_component_readlock.h"

namespace dragonpoop
{

    class model_triangle_instance;
    class model_triangle_instance_ref;

    class model_triangle_instance_readlock : public model_component_readlock
    {

    private:

        model_triangle_instance *t;

    protected:

        //ctor
        model_triangle_instance_readlock( model_triangle_instance *t, dpmutex_readlock *l );
        //dtor
        virtual ~model_triangle_instance_readlock( void );

    public:

        //return instance id
        dpid getInstanceId( void );
        //return triangle id
        dpid getTriangleId( void );

        friend class model_triangle_instance;
    };
    
};

#endif