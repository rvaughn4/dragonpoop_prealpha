
#include "model_group_readlock.h"
#include "model_group.h"

namespace dragonpoop
{

    //ctor
    model_group_readlock::model_group_readlock( model_group *t, dpmutex_readlock *l ) : model_component_readlock( t, l )
    {
        this->t = t;
    }

    //dtor
    model_group_readlock::~model_group_readlock( void )
    {

    }

    //get parent id
    dpid model_group_readlock::getParentId( void )
    {
        return this->t->getParentId();
    }

    //get parent
    model_group_ref *model_group_readlock::getParent( void )
    {
        return this->t->getParent();
    }

    //get name
    void model_group_readlock::getName( std::string *s )
    {
        return this->t->getName( s );
    }

    //get material id
    dpid model_group_readlock::getMaterialId( void )
    {
        return this->t->getMaterialId();
    }

    //returns true if has material
    bool model_group_readlock::hasMaterial( void )
    {
        return this->t->hasMaterial();
    }
};
