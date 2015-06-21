
#ifndef dragonpoop_model_triangle_readlock_h
#define dragonpoop_model_triangle_readlock_h

#include "../model_component/model_component_readlock.h"

namespace dragonpoop
{
    class model_triangle;
    class model_triangle_ref;
    class model_group_ref;

    class model_triangle_readlock : public model_component_readlock
    {

    private:

        model_triangle *t;

    protected:

        //ctor
        model_triangle_readlock( model_triangle *t, dpmutex_readlock *l );
        //dtor
        virtual ~model_triangle_readlock( void );

    public:

        //get parent id
        dpid getParentId( void );
        //get parent
        model_group_ref *getParent( void );

        friend class model_triangle;
    };
    
};

#endif