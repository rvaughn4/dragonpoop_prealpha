
#ifndef dragonpoop_model_material_h
#define dragonpoop_model_material_h

#include "../model_component/model_component_type.h"
#include "../model_component/model_component.h"
#include "../../dpbitmap/dpbitmap.h"

namespace dragonpoop
{

    class model_material_ref;
    class model_material_readlock;
    class model_material_writelock;

    class model_material : public model_component
    {

    private:

        std::string sname;
        dprgba diffuse, ambient, emmissive, specular;
        float shine, opacity, glow;
        dpbitmap *bmDiffuse, *bmAlpha, *bmBump, *bmSpec;

    protected:

        //generate read lock
        virtual shared_obj_readlock *genReadLock( shared_obj *p, dpmutex_readlock *l );
        //generate write lock
        virtual shared_obj_writelock *genWriteLock( shared_obj *p, dpmutex_writelock *l );
        //generate ref
        virtual shared_obj_ref *genRef( shared_obj *p, std::shared_ptr<shared_obj_refkernal> *k );
        //do background processing
        virtual void onRun( dpthread_lock *thd, gfx_writelock *g, model_writelock *m, model_component_writelock *l );
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
        //set glow
        void setGlow( float f );
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
        //get glow
        float getGlow( void );
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

    public:

        //ctor
        model_material( model_writelock *ml, dpid id );
        //dtor
        virtual ~model_material( void );

        friend class model_material_readlock;
        friend class model_material_writelock;
    };
    
};

#endif
