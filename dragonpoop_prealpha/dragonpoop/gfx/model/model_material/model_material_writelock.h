
#ifndef dragonpoop_model_material_writelock_h
#define dragonpoop_model_material_writelock_h

#include "../model_component/model_component_writelock.h"
#include "../../dpvertex/dpvertexes.h"
#include <string>

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

        friend class model_material;
    };
    
};

#endif