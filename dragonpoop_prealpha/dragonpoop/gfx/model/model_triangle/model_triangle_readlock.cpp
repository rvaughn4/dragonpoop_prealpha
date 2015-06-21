
#include "model_triangle_readlock.h"
#include "model_triangle.h"

namespace dragonpoop
{

    //ctor
    model_triangle_readlock::model_triangle_readlock( model_triangle *t, dpmutex_readlock *l ) : model_component_readlock( t, l )
    {
        this->t = t;
    }

    //dtor
    model_triangle_readlock::~model_triangle_readlock( void )
    {

    }

    //get parent id
    dpid model_triangle_readlock::getParentId( void )
    {
        return this->t->getParentId();
    }

    //get parent
    model_group_ref *model_triangle_readlock::getParent( void )
    {
        return this->t->getParent();
    }
    
};
