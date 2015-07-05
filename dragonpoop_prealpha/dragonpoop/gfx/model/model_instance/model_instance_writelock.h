
#ifndef dragonpoop_model_instance_writelock_h
#define dragonpoop_model_instance_writelock_h

#include "../model_component/model_component_writelock.h"

namespace dragonpoop
{

    class model_instance;
    class model_instance_ref;

    class model_instance_writelock : public model_component_writelock
    {

    private:

        model_instance *t;

    protected:

        //ctor
        model_instance_writelock( model_instance *t, dpmutex_writelock *l );
        //dtor
        virtual ~model_instance_writelock( void );

    public:

        friend class model_instance;
    };
    
};

#endif