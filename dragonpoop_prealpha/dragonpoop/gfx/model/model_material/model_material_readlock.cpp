
#include "model_material_readlock.h"
#include "model_material.h"

namespace dragonpoop
{

    //ctor
    model_material_readlock::model_material_readlock( model_material *t, dpmutex_readlock *l ) : model_component_readlock( t, l )
    {
        this->t = t;
    }

    //dtor
    model_material_readlock::~model_material_readlock( void )
    {

    }

    //get name
    void model_material_readlock::getName( std::string *s )
    {
        return this->t->getName( s );
    }

    //get diffuse color
    void model_material_readlock::getDiffuse( dprgba *p )
    {
        this->t->setDiffuse( p );
    }

    //get ambient color
    void model_material_readlock::getAmbient( dprgba *p )
    {
        this->t->setDiffuse( p );
    }

    //get emmissive color
    void model_material_readlock::getEmmissive( dprgba *p )
    {
        this->t->setDiffuse( p );
    }

    //get specular color
    void model_material_readlock::getSpecular( dprgba *p )
    {
        this->t->setDiffuse( p );
    }

    //get shine
    float model_material_readlock::getShine( void )
    {
        return this->t->getShine();
    }

    //get opacity
    float model_material_readlock::getOpacity( void )
    {
        return this->t->getOpacity();
    }
    
};
