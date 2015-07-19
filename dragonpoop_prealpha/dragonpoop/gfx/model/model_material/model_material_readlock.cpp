
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

    //returns true if has diffuse texture
    bool model_material_readlock::hasDiffuseTexture( void )
    {
        return this->t->hasDiffuseTexture();
    }

    //returns true if has alpha mask texture
    bool model_material_readlock::hasAlphaMaskTexture( void )
    {
        return this->t->hasAlphaMaskTexture();
    }

    //returns true if has bump map texture
    bool model_material_readlock::hasBumpMapTexture( void )
    {
        return this->t->hasBumpMapTexture();
    }

    //returns true if has spec map texture
    bool model_material_readlock::hasSpecularMapTexture( void )
    {
        return this->t->hasSpecularMapTexture();
    }

    //copy diffuse texture, returns false is none exist
    bool model_material_readlock::getDiffuseTexture( dpbitmap *c )
    {
        return this->t->getDiffuseTexture( c );
    }

    //copy alpha texture, returns false is none exist
    bool model_material_readlock::getAlphaMapTexture( dpbitmap *c )
    {
        return this->t->getAlphaMapTexture( c );
    }

    //copy bump map texture, returns false is none exist
    bool model_material_readlock::getBumpMapTexture( dpbitmap *c )
    {
        return this->t->getBumpMapTexture( c );
    }

    //copy specular texture, returns false is none exist
    bool model_material_readlock::getSpecularMapTexture( dpbitmap *c )
    {
        return this->t->getSpecularMapTexture( c );
    }

};
