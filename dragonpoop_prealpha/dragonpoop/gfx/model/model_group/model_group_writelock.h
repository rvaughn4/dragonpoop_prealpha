
#ifndef dragonpoop_model_group_writelock_h
#define dragonpoop_model_group_writelock_h

#include "../model_component/model_component_writelock.h"
#include <string>

namespace dragonpoop
{
    class model_group;
    class model_group_ref;

    class model_group_writelock : public model_component_writelock
    {

    private:

        model_group *t;

    protected:

        //ctor
        model_group_writelock( model_group *t, dpmutex_writelock *l );
        //dtor
        virtual ~model_group_writelock( void );

    public:

        //get parent id
        dpid getParentId( void );
        //get parent
        model_group_ref *getParent( void );
        //get name
        void getName( std::string *s );
        //set name
        void setName( std::string *s );
        //set material id
        void setMaterialId( dpid id );
        //get material id
        dpid getMaterialId( void );
        //returns true if has material
        bool hasMaterial( void );

        friend class model_group;
    };
    
};

#endif