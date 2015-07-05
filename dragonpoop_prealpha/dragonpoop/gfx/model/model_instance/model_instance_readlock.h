
#ifndef dragonpoop_model_instance_readlock_h
#define dragonpoop_model_instance_readlock_h

#include "../model_component/model_component_readlock.h"

namespace dragonpoop
{

    class model_instance;
    class model_instance_ref;

    class model_instance_readlock : public model_component_readlock
    {

    private:

        model_instance *t;

    protected:

        //ctor
        model_instance_readlock( model_instance *t, dpmutex_readlock *l );
        //dtor
        virtual ~model_instance_readlock( void );

    public:

        friend class model_instance;
    };
    
};

#endif