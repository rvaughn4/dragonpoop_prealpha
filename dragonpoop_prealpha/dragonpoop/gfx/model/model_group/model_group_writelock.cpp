
#include "model_group_writelock.h"
#include "model_group.h"

namespace dragonpoop
{

    //ctor
    model_group_writelock::model_group_writelock( model_group *t, dpmutex_writelock *l ) : model_component_writelock( t, l )
    {
        this->t = t;
    }

    //dtor
    model_group_writelock::~model_group_writelock( void )
    {

    }

    //get parent id
    dpid model_group_writelock::getParentId( void )
    {
        return this->t->getParentId();
    }

    //get parent
    model_group_ref *model_group_writelock::getParent( void )
    {
        return this->t->getParent();
    }

    //get name
    void model_group_writelock::getName( std::string *s )
    {
        return this->t->getName( s );
    }

    //set name
    void model_group_writelock::setName( std::string *s )
    {
        return this->t->setName( s );
    }

    //set material id
    void model_group_writelock::setMaterialId( dpid id )
    {
        this->t->setMaterialId( id );
    }

    //get material id
    dpid model_group_writelock::getMaterialId( void )
    {
        return this->t->getMaterialId();
    }

    //returns true if has material
    bool model_group_writelock::hasMaterial( void )
    {
        return this->t->hasMaterial();
    }

};
