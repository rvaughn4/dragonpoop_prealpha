
#include "model_triangle_instance_readlock.h"
#include "model_triangle_instance.h"

namespace dragonpoop
{

    //ctor
    model_triangle_instance_readlock::model_triangle_instance_readlock( model_triangle_instance *t, dpmutex_readlock *l ) : model_component_readlock( t, l )
    {
        this->t = t;
    }

    //dtor
    model_triangle_instance_readlock::~model_triangle_instance_readlock( void )
    {

    }

    //return instance id
    dpid model_triangle_instance_readlock::getInstanceId( void )
    {
        return this->t->getInstanceId();
    }

    //return triangle id
    dpid model_triangle_instance_readlock::getTriangleId( void )
    {
        return this->t->getTriangleId();
    }

    //return group id
    dpid model_triangle_instance_readlock::getGroupId( void )
    {
        return this->t->getGroupId();
    }

    //get vertexes
    void model_triangle_instance_readlock::getVertexes( dpvertexindex_buffer *b )
    {
        this->t->getVertexes( b );
    }

};
