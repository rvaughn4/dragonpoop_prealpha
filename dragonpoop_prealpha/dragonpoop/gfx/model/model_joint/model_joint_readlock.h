
#ifndef dragonpoop_model_joint_readlock_h
#define dragonpoop_model_joint_readlock_h

#include "../model_component/model_component_readlock.h"
#include "../../dpvertex/dpvertexes.h"
#include <string>

namespace dragonpoop
{
    class model_joint;
    class model_joint_ref;

    class model_joint_readlock : public model_component_readlock
    {

    private:

        model_joint *t;

    protected:

        //ctor
        model_joint_readlock( model_joint *t, dpmutex_readlock *l );
        //dtor
        virtual ~model_joint_readlock( void );

    public:

        //get position
        void getPosition( dpxyzw *p );
        //get roatation
        void getRotation( dpxyzw *p );
        //get name
        void getName( std::string *s );

        friend class model_joint;
    };
    
};

#endif