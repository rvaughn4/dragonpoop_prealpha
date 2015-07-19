
#include "model_material.h"
#include "model_material_ref.h"
#include "model_material_readlock.h"
#include "model_material_writelock.h"

namespace dragonpoop
{

    //ctor
    model_material::model_material( model_writelock *ml, dpid id ) : model_component( ml, id, model_component_type_material, 0 )
    {
        this->shine = 0.0f;
        this->opacity = 1.0f;
        this->glow = 0.0f;
        this->diffuse.r = 1.0f;
        this->diffuse.g = 1.0f;
        this->diffuse.b = 1.0f;
        this->diffuse.a = 1.0f;
        this->ambient = this->diffuse;
        this->specular = this->diffuse;
        this->emmissive = this->diffuse;
        this->bmDiffuse = this->bmAlpha = this->bmBump = this->bmSpec = 0;
    }

    //dtor
    model_material::~model_material( void )
    {
        model_component_writelock *l;
        shared_obj_guard g;

        l = (model_component_writelock *)g.writeLock( this );
        g.unlock();
        delete this->bmDiffuse;
        delete this->bmAlpha;
        delete this->bmBump;
        delete this->bmSpec;
    }

    //get name
    void model_material::getName( std::string *s )
    {
        *s = this->sname;
    }

    //set name
    void model_material::setName( std::string *s )
    {
        this->sname = *s;
    }

    //set diffuse color
    void model_material::setDiffuse( dprgba *p )
    {
        this->diffuse = *p;
    }

    //set ambient color
    void model_material::setAmbient( dprgba *p )
    {
        this->ambient = *p;
    }

    //set emmissive color
    void model_material::setEmmissive( dprgba *p )
    {
        this->emmissive = *p;
    }

    //set specular color
    void model_material::setSpecular( dprgba *p )
    {
        this->specular = *p;
    }

    //set shine
    void model_material::setShine( float f )
    {
        this->shine = f;
    }

    //set opacity
    void model_material::setOpacity( float f )
    {
        this->opacity = f;
    }

    //set glow
    void model_material::setGlow( float f )
    {
        this->glow = f;
    }
    
    //get diffuse color
    void model_material::getDiffuse( dprgba *p )
    {
        *p = this->diffuse;
    }

    //get ambient color
    void model_material::getAmbient( dprgba *p )
    {
        *p = this->ambient;
    }

    //get emmissive color
    void model_material::getEmmissive( dprgba *p )
    {
        *p = this->emmissive;
    }

    //get specular color
    void model_material::getSpecular( dprgba *p )
    {
        *p = this->specular;
    }

    //get shine
    float model_material::getShine( void )
    {
        return this->shine;
    }

    //get opacity
    float model_material::getOpacity( void )
    {
        return this->opacity;
    }

    //get glow
    float model_material::getGlow( void )
    {
        return this->glow;
    }

    //generate read lock
    shared_obj_readlock *model_material::genReadLock( shared_obj *p, dpmutex_readlock *l )
    {
        return new model_material_readlock( (model_material *)p, l );
    }

    //generate write lock
    shared_obj_writelock *model_material::genWriteLock( shared_obj *p, dpmutex_writelock *l )
    {
        return new model_material_writelock( (model_material *)p, l );
    }

    //generate ref
    shared_obj_ref *model_material::genRef( shared_obj *p, std::shared_ptr<shared_obj_refkernal> *k )
    {
        return new model_material_ref( (model_material *)p, k );
    }

    //do background processing
    void model_material::onRun( dpthread_lock *thd, gfx_writelock *g, model_writelock *m, model_component_writelock *l )
    {

    }

    //returns true if has diffuse texture
    bool model_material::hasDiffuseTexture( void )
    {
        return this->bmDiffuse != 0;
    }

    //returns true if has alpha mask texture
    bool model_material::hasAlphaMaskTexture( void )
    {
        return this->bmAlpha != 0;
    }

    //returns true if has bump map texture
    bool model_material::hasBumpMapTexture( void )
    {
        return this->bmBump != 0;
    }

    //returns true if has spec map texture
    bool model_material::hasSpecularMapTexture( void )
    {
        return this->bmSpec != 0;
    }

    //copy diffuse texture, returns false is none exist
    bool model_material::getDiffuseTexture( dpbitmap *c )
    {
        dpbitmap *a = this->bmDiffuse;
        if( !a )
            return 0;
        c->copy( a );
        return 1;
    }

    //copy alpha texture, returns false is none exist
    bool model_material::getAlphaMapTexture( dpbitmap *c )
    {
        dpbitmap *a = this->bmAlpha;
        if( !a )
            return 0;
        c->copy( a );
        return 1;
    }

    //copy bump map texture, returns false is none exist
    bool model_material::getBumpMapTexture( dpbitmap *c )
    {
        dpbitmap *a = this->bmBump;
        if( !a )
            return 0;
        c->copy( a );
        return 1;
    }

    //copy specular texture, returns false is none exist
    bool model_material::getSpecularMapTexture( dpbitmap *c )
    {
        dpbitmap *a = this->bmSpec;
        if( !a )
            return 0;
        c->copy( a );
        return 1;
    }

    //set diffuse texture
    void model_material::setDiffuseTexture( dpbitmap *c )
    {
        dpbitmap **a = &this->bmDiffuse;
        if( *a )
            delete *a;
        *a = 0;
        if( !c )
            return;
        *a = new dpbitmap();
        ( *a )->copy( c );
    }

    //set alpha texture
    void model_material::setAlphaMapTexture( dpbitmap *c )
    {
        dpbitmap **a = &this->bmAlpha;
        if( *a )
            delete *a;
        *a = 0;
        if( !c )
            return;
        *a = new dpbitmap();
        ( *a )->copy( c );
    }

    //set bump map texture
    void model_material::setBumpMapTexture( dpbitmap *c )
    {
        dpbitmap **a = &this->bmBump;
        if( *a )
            delete *a;
        *a = 0;
        if( !c )
            return;
        *a = new dpbitmap();
        ( *a )->copy( c );
    }

    //set specular texture
    void model_material::setSpecularMapTexture( dpbitmap *c )
    {
        dpbitmap **a = &this->bmSpec;
        if( *a )
            delete *a;
        *a = 0;
        if( !c )
            return;
        *a = new dpbitmap();
        ( *a )->copy( c );
    }

};
