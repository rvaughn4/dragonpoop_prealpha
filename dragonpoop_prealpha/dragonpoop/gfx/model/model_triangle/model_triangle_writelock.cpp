
#include "model_triangle_writelock.h"
#include "model_triangle.h"

namespace dragonpoop
{

    //ctor
    model_triangle_writelock::model_triangle_writelock( model_triangle *t, dpmutex_writelock *l ) : model_component_writelock( t, l )
    {
        this->t = t;
    }

    //dtor
    model_triangle_writelock::~model_triangle_writelock( void )
    {

    }

    //get parent id
    dpid model_triangle_writelock::getParentId( void )
    {
        return this->t->getParentId();
    }

    //get parent
    model_group_ref *model_triangle_writelock::getParent( void )
    {
        return this->t->getParent();
    }

};
