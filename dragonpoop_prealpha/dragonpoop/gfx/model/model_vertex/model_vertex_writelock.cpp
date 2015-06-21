
#include "model_vertex_writelock.h"
#include "model_vertex.h"

namespace dragonpoop
{

    //ctor
    model_vertex_writelock::model_vertex_writelock( model_vertex *t, dpmutex_writelock *l ) : model_component_writelock( t, l )
    {
        this->t = t;
    }

    //dtor
    model_vertex_writelock::~model_vertex_writelock( void )
    {

    }

    //get position
    void model_vertex_writelock::getPosition( dpxyzw *p )
    {
        this->t->getPosition( p );
    }

    //get position
    void model_vertex_writelock::getPosition( dpxyzw_f *p )
    {
        this->t->getPosition( p );
    }

    //get position
    void model_vertex_writelock::getPosition( dpxyz_f *p )
    {
        this->t->getPosition( p );
    }

    //get position
    void model_vertex_writelock::setPosition( dpxyzw *p )
    {
        this->t->setPosition( p );
    }

    //get position
    void model_vertex_writelock::setPosition( dpxyzw_f *p )
    {
        this->t->setPosition( p );
    }

    //get position
    void model_vertex_writelock::setPosition( dpxyz_f *p )
    {
        this->t->setPosition( p );
    }

};
