
#ifndef dragonpoop_model_joint_writelock_h
#define dragonpoop_model_joint_writelock_h

#include "../model_component/model_component_writelock.h"
#include "../../dpvertex/dpvertexes.h"
#include <string>

namespace dragonpoop
{
    class model_joint;
    class model_joint_ref;

    class model_joint_writelock : public model_component_writelock
    {

    private:

        model_joint *t;

    protected:

        //ctor
        model_joint_writelock( model_joint *t, dpmutex_writelock *l );
        //dtor
        virtual ~model_joint_writelock( void );

    public:

        //get position
        void getPosition( dpxyzw *p );
        //get roatation
        void getRotation( dpxyzw *p );
        //get name
        void getName( std::string *s );
        //set position
        void setPosition( dpxyzw *p );
        //set roatation
        void setRotation( dpxyzw *p );
        //set name
        void setName( std::string *s );
        //return parent id
        dpid getParentId( void );
        //return parent
        model_joint_ref *getParent( void );

        friend class model_joint;
    };
    
};

#endif