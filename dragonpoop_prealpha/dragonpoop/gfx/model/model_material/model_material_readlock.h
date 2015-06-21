
#ifndef dragonpoop_model_material_readlock_h
#define dragonpoop_model_material_readlock_h

#include "../model_component/model_component_readlock.h"
#include "../../dpvertex/dpvertexes.h"
#include <string>

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

        friend class model_material;
    };
    
};

#endif