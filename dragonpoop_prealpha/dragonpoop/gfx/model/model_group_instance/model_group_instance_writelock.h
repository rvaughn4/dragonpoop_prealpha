
#ifndef dragonpoop_model_group_instance_writelock_h
#define dragonpoop_model_group_instance_writelock_h

#include "../model_component/model_component_writelock.h"

namespace dragonpoop
{

    class model_group_instance;
    class model_group_instance_ref;

    class model_group_instance_writelock : public model_component_writelock
    {

    private:

        model_group_instance *t;

    protected:

        //ctor
        model_group_instance_writelock( model_group_instance *t, dpmutex_writelock *l );
        //dtor
        virtual ~model_group_instance_writelock( void );

    public:

        //return instance id
        dpid getInstanceId( void );
        //return group id
        dpid getGroupId( void );
        //return partent id
        dpid getParentId( void );
        //returns true if has renderer
        bool hasRenderer( void );
        //set renderer
        void setRenderer( shared_obj_writelock *r );
        //get renderer
        shared_obj_ref *getRenderer( void );

        friend class model_group_instance;
    };
    
};

#endif