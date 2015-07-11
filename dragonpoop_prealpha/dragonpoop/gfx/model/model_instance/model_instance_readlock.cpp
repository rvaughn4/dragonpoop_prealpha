
#include "model_instance_readlock.h"
#include "model_instance.h"

namespace dragonpoop
{

    //ctor
    model_instance_readlock::model_instance_readlock( model_instance *t, dpmutex_readlock *l ) : model_component_readlock( t, l )
    {
        this->t = t;
    }

    //dtor
    model_instance_readlock::~model_instance_readlock( void )
    {

    }


    //get group instances
    unsigned int model_instance_readlock::getGroups( std::list<model_group_instance_ref *> *l )
    {
        return this->t->getGroups( l );
    }

    //get group instances by parent
    unsigned int model_instance_readlock::getGroupsByParent( dpid parent_id, std::list<model_group_instance_ref *> *l )
    {
        return this->t->getGroupsByParent( parent_id, l );
    }

    //release list returned by getGroups()
    void model_instance_readlock::releaseGetGroups( std::list<model_group_instance_ref *> *l )
    {
        model_instance::releaseGetGroups( l );
    }

    //get triangle instances
    unsigned int model_instance_readlock::getTriangles( std::list<model_triangle_instance_ref *> *l )
    {
        return this->t->getTriangles( l );
    }

    //get triangle instances by group
    unsigned int model_instance_readlock::getTrianglesByGroup( dpid group_id, std::list<model_triangle_instance_ref *> *l )
    {
        return this->t->getTrianglesByGroup( group_id, l );
    }

    //release list returned by getTriangles()
    void model_instance_readlock::releaseGetTriangles( std::list<model_triangle_instance_ref *> *l )
    {
        model_instance::releaseGetTriangles( l );
    }

};
