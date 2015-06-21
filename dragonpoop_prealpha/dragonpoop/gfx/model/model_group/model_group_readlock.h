
#ifndef dragonpoop_model_group_readlock_h
#define dragonpoop_model_group_readlock_h

#include "../model_component/model_component_readlock.h"
#include <string>

namespace dragonpoop
{
    class model_group;
    class model_group_ref;

    class model_group_readlock : public model_component_readlock
    {

    private:

        model_group *t;

    protected:

        //ctor
        model_group_readlock( model_group *t, dpmutex_readlock *l );
        //dtor
        virtual ~model_group_readlock( void );

    public:

        //get parent id
        dpid getParentId( void );
        //get parent
        model_group_ref *getParent( void );
        //get name
        void getName( std::string *s );

        friend class model_group;
    };
    
};

#endif