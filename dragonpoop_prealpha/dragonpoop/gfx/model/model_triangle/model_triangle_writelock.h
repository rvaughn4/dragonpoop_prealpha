
#ifndef dragonpoop_model_triangle_writelock_h
#define dragonpoop_model_triangle_writelock_h

#include "../model_component/model_component_writelock.h"

namespace dragonpoop
{
    class model_triangle;
    class model_triangle_ref;
    class model_group_ref;

    class model_triangle_writelock : public model_component_writelock
    {

    private:

        model_triangle *t;

    protected:

        //ctor
        model_triangle_writelock( model_triangle *t, dpmutex_writelock *l );
        //dtor
        virtual ~model_triangle_writelock( void );

    public:

        //get parent id
        dpid getParentId( void );
        //get parent
        model_group_ref *getParent( void );

        friend class model_triangle;
    };
    
};

#endif