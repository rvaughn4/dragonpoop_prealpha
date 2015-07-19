
#ifndef dragonpoop_model_material_writelock_h
#define dragonpoop_model_material_writelock_h

#include "../model_component/model_component_writelock.h"
#include "../../dpbitmap/dpbitmap.h"

namespace dragonpoop
{
    class model_material;
    class model_material_ref;

    class model_material_writelock : public model_component_writelock
    {

    private:

        model_material *t;

    protected:

        //ctor
        model_material_writelock( model_material *t, dpmutex_writelock *l );
        //dtor
        virtual ~model_material_writelock( void );

    public:

        //get name
        void getName( std::string *s );
        //set name
        void setName( std::string *s );
        //set diffuse color
        void setDiffuse( dprgba *p );
        //set ambient color
        void setAmbient( dprgba *p );
        //set emmissive color
        void setEmmissive( dprgba *p );
        //set specular color
        void setSpecular( dprgba *p );
        //set shine
        void setShine( float f );
        //set opacity
        void setOpacity( float f );
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
        //set diffuse texture
        void setDiffuseTexture( dpbitmap *c );
        //set alpha texture
        void setAlphaMapTexture( dpbitmap *c );
        //set bump map texture
        void setBumpMapTexture( dpbitmap *c );
        //set specular texture
        void setSpecularMapTexture( dpbitmap *c );

        friend class model_material;
    };
    
};

#endif