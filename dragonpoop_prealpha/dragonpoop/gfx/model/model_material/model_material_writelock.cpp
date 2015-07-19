
#include "model_material_writelock.h"
#include "model_material.h"

namespace dragonpoop
{

    //ctor
    model_material_writelock::model_material_writelock( model_material *t, dpmutex_writelock *l ) : model_component_writelock( t, l )
    {
        this->t = t;
    }

    //dtor
    model_material_writelock::~model_material_writelock( void )
    {

    }

    //get name
    void model_material_writelock::getName( std::string *s )
    {
        return this->t->getName( s );
    }

    //set name
    void model_material_writelock::setName( std::string *s )
    {
        return this->t->setName( s );
    }

    //set diffuse color
    void model_material_writelock::setDiffuse( dprgba *p )
    {
        this->t->setDiffuse( p );
    }

    //set ambient color
    void model_material_writelock::setAmbient( dprgba *p )
    {
        this->t->setAmbient( p );
    }

    //set emmissive color
    void model_material_writelock::setEmmissive( dprgba *p )
    {
        this->t->setEmmissive( p );
    }

    //set specular color
    void model_material_writelock::setSpecular( dprgba *p )
    {
        this->t->setSpecular( p );
    }

    //set shine
    void model_material_writelock::setShine( float f )
    {
        this->t->setShine( f );
    }

    //set opacity
    void model_material_writelock::setOpacity( float f )
    {
        this->t->setOpacity( f );
    }

    //get diffuse color
    void model_material_writelock::getDiffuse( dprgba *p )
    {
        this->t->setDiffuse( p );
    }

    //get ambient color
    void model_material_writelock::getAmbient( dprgba *p )
    {
        this->t->setDiffuse( p );
    }

    //get emmissive color
    void model_material_writelock::getEmmissive( dprgba *p )
    {
        this->t->setDiffuse( p );
    }

    //get specular color
    void model_material_writelock::getSpecular( dprgba *p )
    {
        this->t->setDiffuse( p );
    }

    //get shine
    float model_material_writelock::getShine( void )
    {
        return this->t->getShine();
    }

    //get opacity
    float model_material_writelock::getOpacity( void )
    {
        return this->t->getOpacity();
    }

    //returns true if has diffuse texture
    bool model_material_writelock::hasDiffuseTexture( void )
    {
        return this->t->hasDiffuseTexture();
    }

    //returns true if has alpha mask texture
    bool model_material_writelock::hasAlphaMaskTexture( void )
    {
        return this->t->hasAlphaMaskTexture();
    }

    //returns true if has bump map texture
    bool model_material_writelock::hasBumpMapTexture( void )
    {
        return this->t->hasBumpMapTexture();
    }

    //returns true if has spec map texture
    bool model_material_writelock::hasSpecularMapTexture( void )
    {
        return this->t->hasSpecularMapTexture();
    }

    //copy diffuse texture, returns false is none exist
    bool model_material_writelock::getDiffuseTexture( dpbitmap *c )
    {
        return this->t->getDiffuseTexture( c );
    }

    //copy alpha texture, returns false is none exist
    bool model_material_writelock::getAlphaMapTexture( dpbitmap *c )
    {
        return this->t->getAlphaMapTexture( c );
    }

    //copy bump map texture, returns false is none exist
    bool model_material_writelock::getBumpMapTexture( dpbitmap *c )
    {
        return this->t->getBumpMapTexture( c );
    }

    //copy specular texture, returns false is none exist
    bool model_material_writelock::getSpecularMapTexture( dpbitmap *c )
    {
        return this->t->getSpecularMapTexture( c );
    }

    //set diffuse texture
    void model_material_writelock::setDiffuseTexture( dpbitmap *c )
    {
        this->t->setDiffuseTexture( c );
    }

    //set alpha texture
    void model_material_writelock::setAlphaMapTexture( dpbitmap *c )
    {
        this->t->setAlphaMapTexture( c );
    }

    //set bump map texture
    void model_material_writelock::setBumpMapTexture( dpbitmap *c )
    {
        this->t->setBumpMapTexture( c );
    }

    //set specular texture
    void model_material_writelock::setSpecularMapTexture( dpbitmap *c )
    {
        this->t->setSpecularMapTexture( c );
    }

};
