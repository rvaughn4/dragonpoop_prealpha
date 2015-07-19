
#include "model_instance_writelock.h"
#include "model_instance.h"

namespace dragonpoop
{

    //ctor
    model_instance_writelock::model_instance_writelock( model_instance *t, dpmutex_writelock *l ) : model_component_writelock( t, l )
    {
        this->t = t;
    }

    //dtor
    model_instance_writelock::~model_instance_writelock( void )
    {

    }

    //get group instances
    unsigned int model_instance_writelock::getGroups( std::list<model_group_instance_ref *> *l )
    {
        return this->t->getGroups( l );
    }

    //get group instances by parent
    unsigned int model_instance_writelock::getGroupsByParent( dpid parent_id, std::list<model_group_instance_ref *> *l )
    {
        return this->t->getGroupsByParent( parent_id, l );
    }

    //release list returned by getGroups()
    void model_instance_writelock::releaseGetGroups( std::list<model_group_instance_ref *> *l )
    {
        model_instance::releaseGetGroups( l );
    }

    //get triangle instances
    unsigned int model_instance_writelock::getTriangles( std::list<model_triangle_instance_ref *> *l )
    {
        return this->t->getTriangles( l );
    }

    //get triangle instances by group
    unsigned int model_instance_writelock::getTrianglesByGroup( dpid group_id, std::list<model_triangle_instance_ref *> *l )
    {
        return this->t->getTrianglesByGroup( group_id, l );
    }

    //release list returned by getTriangles()
    void model_instance_writelock::releaseGetTriangles( std::list<model_triangle_instance_ref *> *l )
    {
        model_instance::releaseGetTriangles( l );
    }

    //returns true if has renderer
    bool model_instance_writelock::hasRenderer( void )
    {
        return this->t->hasRenderer();
    }

    //set renderer
    void model_instance_writelock::setRenderer( shared_obj_writelock *r )
    {
        this->t->setRenderer( r );
    }

    //get renderer
    shared_obj_ref *model_instance_writelock::getRenderer( void )
    {
        return this->t->getRenderer();
    }

};
