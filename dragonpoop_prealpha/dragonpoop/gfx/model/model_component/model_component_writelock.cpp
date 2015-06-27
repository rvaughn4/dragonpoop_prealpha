
#include "model_component_writelock.h"
#include "model_component.h"

namespace dragonpoop
{

    //ctor
    model_component_writelock::model_component_writelock( model_component *t, dpmutex_writelock *l ) : shared_obj_writelock( t, l )
    {
        this->t = t;
    }

    //dtor
    model_component_writelock::~model_component_writelock( void )
    {

    }

    //return core
    core *model_component_writelock::getCore( void )
    {
        return this->t->getCore();
    }

    //get id
    dpid model_component_writelock::getId( void )
    {
        return this->t->getId();
    }

    //get type
    uint16_t model_component_writelock::getType( void )
    {
        return this->t->getType();
    }

    //returns true if alive
    bool model_component_writelock::isAlive( void )
    {
        return this->t->isAlive();
    }

    //kill model
    void model_component_writelock::kill( void )
    {
        this->t->kill();
    }

    //run model
    void model_component_writelock::run( dpthread_lock *thd, gfx_writelock *g, model_writelock *m )
    {
        this->t->run( thd, g, m, this );
    }

    //return model
    model_ref *model_component_writelock::getModel( void )
    {
        return this->t->getModel();
    }

    //get comment
    void model_component_writelock::getComment( std::string *s )
    {
        this->t->getComment( s );
    }

    //set comment
    void model_component_writelock::setComment( std::string *s )
    {
        this->t->setComment( s );
    }

    //add comment
    void model_component_writelock::addComment( std::string *s )
    {
        this->t->addComment( s );
    }

};
