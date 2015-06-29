
#include "model_joint_writelock.h"
#include "model_joint.h"

namespace dragonpoop
{

    //ctor
    model_joint_writelock::model_joint_writelock( model_joint *t, dpmutex_writelock *l ) : model_component_writelock( t, l )
    {
        this->t = t;
    }

    //dtor
    model_joint_writelock::~model_joint_writelock( void )
    {

    }

    //get position
    void model_joint_writelock::getPosition( dpxyzw *p )
    {
        this->t->getPosition( p );
    }

    //get roatation
    void model_joint_writelock::getRotation( dpxyzw *p )
    {
        this->t->getRotation( p );
    }

    //get name
    void model_joint_writelock::getName( std::string *s )
    {
        this->t->getName( s );
    }

    //set position
    void model_joint_writelock::setPosition( dpxyzw *p )
    {
        this->t->setPosition( p );
    }

    //set roatation
    void model_joint_writelock::setRotation( dpxyzw *p )
    {
        this->t->setRotation( p );
    }

    //set name
    void model_joint_writelock::setName( std::string *s )
    {
        this->t->setName( s );
    }

    //return parent id
    dpid model_joint_writelock::getParentId( void )
    {
        return this->t->getParentId();
    }

    //return parent
    model_joint_ref *model_joint_writelock::getParent( void )
    {
        return this->t->getParent();
    }

};
