
#include "model_joint_readlock.h"
#include "model_joint.h"

namespace dragonpoop
{

    //ctor
    model_joint_readlock::model_joint_readlock( model_joint *t, dpmutex_readlock *l ) : model_component_readlock( t, l )
    {
        this->t = t;
    }

    //dtor
    model_joint_readlock::~model_joint_readlock( void )
    {

    }

    //get position
    void model_joint_readlock::getPosition( dpxyzw *p )
    {
        this->t->getPosition( p );
    }

    //get roatation
    void model_joint_readlock::getRotation( dpxyzw *p )
    {
        this->t->getRotation( p );
    }

    //get name
    void model_joint_readlock::getName( std::string *s )
    {
        this->t->getName( s );
    }

    //return parent id
    dpid model_joint_readlock::getParentId( void )
    {
        return this->t->getParentId();
    }

    //return parent
    model_joint_ref *model_joint_readlock::getParent( void )
    {
        return this->t->getParent();
    }

};
