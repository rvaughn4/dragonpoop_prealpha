
#ifndef dragonpoop_model_group_instance_readlock_h
#define dragonpoop_model_group_instance_readlock_h

#include "../model_component/model_component_readlock.h"

namespace dragonpoop
{

    class model_group_instance;
    class model_group_instance_ref;

    class model_group_instance_readlock : public model_component_readlock
    {

    private:

        model_group_instance *t;

    protected:

        //ctor
        model_group_instance_readlock( model_group_instance *t, dpmutex_readlock *l );
        //dtor
        virtual ~model_group_instance_readlock( void );

    public:

        //return instance id
        dpid getInstanceId( void );
        //return group id
        dpid getGroupId( void );
        //return partent id
        dpid getParentId( void );

        friend class model_group_instance;
    };
    
};

#endif