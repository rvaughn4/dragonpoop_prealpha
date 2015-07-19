
#include "model_group_instance_readlock.h"
#include "model_group_instance.h"

namespace dragonpoop
{

    //ctor
    model_group_instance_readlock::model_group_instance_readlock( model_group_instance *t, dpmutex_readlock *l ) : model_component_readlock( t, l )
    {
        this->t = t;
    }

    //dtor
    model_group_instance_readlock::~model_group_instance_readlock( void )
    {

    }

    //return instance id
    dpid model_group_instance_readlock::getInstanceId( void )
    {
        return this->t->getInstanceId();
    }

    //return group id
    dpid model_group_instance_readlock::getGroupId( void )
    {
        return this->t->getGroupId();
    }

    //return partent id
    dpid model_group_instance_readlock::getParentId( void )
    {
        return this->t->getParentId();
    }

    //returns true if has renderer
    bool model_group_instance_readlock::hasRenderer( void )
    {
        return this->t->hasRenderer();
    }

    //get renderer
    shared_obj_ref *model_group_instance_readlock::getRenderer( void )
    {
        return this->t->getRenderer();
    }

    //get vertexes
    void model_group_instance_readlock::getVertexes( dpvertexindex_buffer *b )
    {
        this->t->getVertexes( b );
    }

    //return material id
    dpid model_group_instance_readlock::getMaterialId( void )
    {
        return this->t->getMaterialId();
    }

    //returns true if has material
    bool model_group_instance_readlock::hasMaterial( void )
    {
        return this->t->hasMaterial();
    }
};
