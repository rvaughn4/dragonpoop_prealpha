
#include "model_vertex_readlock.h"
#include "model_vertex.h"

namespace dragonpoop
{

    //ctor
    model_vertex_readlock::model_vertex_readlock( model_vertex *t, dpmutex_readlock *l ) : model_component_readlock( t, l )
    {
        this->t = t;
    }

    //dtor
    model_vertex_readlock::~model_vertex_readlock( void )
    {

    }

    //get position
    void model_vertex_readlock::getPosition( dpxyzw *p )
    {
        this->t->getPosition( p );
    }

    //get position
    void model_vertex_readlock::getPosition( dpxyzw_f *p )
    {
        this->t->getPosition( p );
    }

    //get position
    void model_vertex_readlock::getPosition( dpxyz_f *p )
    {
        this->t->getPosition( p );
    }

};
