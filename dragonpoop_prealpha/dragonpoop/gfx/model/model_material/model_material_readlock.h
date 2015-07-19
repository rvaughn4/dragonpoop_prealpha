
#ifndef dragonpoop_model_material_readlock_h
#define dragonpoop_model_material_readlock_h

#include "../model_component/model_component_readlock.h"
#include "../../dpbitmap/dpbitmap.h"

namespace dragonpoop
{
    class model_material;
    class model_material_ref;

    class model_material_readlock : public model_component_readlock
    {

    private:

        model_material *t;

    protected:

        //ctor
        model_material_readlock( model_material *t, dpmutex_readlock *l );
        //dtor
        virtual ~model_material_readlock( void );

    public:

        //get name
        void getName( std::string *s );
        //get diffuse color
        void getDiffuse( dprgba *p );
        //get ambient color
        void getAmbient( dprgba *p );
        //get emmissive color
        void getEmmissive( dprgba *p );
        //get specular color
        void getSpecular( dprgba *p );
        //get shine
        float getShine( void );
        //get opacity
        float getOpacity( void );
        //returns true if has diffuse texture
        bool hasDiffuseTexture( void );
        //returns true if has alpha mask texture
        bool hasAlphaMaskTexture( void );
        //returns true if has bump map texture
        bool hasBumpMapTexture( void );
        //returns true if has spec map texture
        bool hasSpecularMapTexture( void );
        //copy diffuse texture, returns false is none exist
        bool getDiffuseTexture( dpbitmap *c );
        //copy alpha texture, returns false is none exist
        bool getAlphaMapTexture( dpbitmap *c );
        //copy bump map texture, returns false is none exist
        bool getBumpMapTexture( dpbitmap *c );
        //copy specular texture, returns false is none exist
        bool getSpecularMapTexture( dpbitmap *c );

        friend class model_material;
    };
    
};

#endif