
#include "model_group_instance_writelock.h"
#include "model_group_instance.h"

namespace dragonpoop
{

    //ctor
    model_group_instance_writelock::model_group_instance_writelock( model_group_instance *t, dpmutex_writelock *l ) : model_component_writelock( t, l )
    {
        this->t = t;
    }

    //dtor
    model_group_instance_writelock::~model_group_instance_writelock( void )
    {

    }

    //return instance id
    dpid model_group_instance_writelock::getInstanceId( void )
    {
        return this->t->getInstanceId();
    }

    //return group id
    dpid model_group_instance_writelock::getGroupId( void )
    {
        return this->t->getGroupId();
    }

    //return partent id
    dpid model_group_instance_writelock::getParentId( void )
    {
        return this->t->getParentId();
    }

    //returns true if has renderer
    bool model_group_instance_writelock::hasRenderer( void )
    {
        return this->t->hasRenderer();
    }

    //set renderer
    void model_group_instance_writelock::setRenderer( shared_obj_writelock *r )
    {
        this->t->setRenderer( r );
    }

    //get renderer
    shared_obj_ref *model_group_instance_writelock::getRenderer( void )
    {
        return this->t->getRenderer();
    }

    //get vertexes
    void model_group_instance_writelock::getVertexes( dpvertexindex_buffer *b )
    {
        this->t->getVertexes( b );
    }

    //sync group
    void model_group_instance_writelock::sync( model_writelock *ml )
    {
        this->t->sync( ml );
    }

};
