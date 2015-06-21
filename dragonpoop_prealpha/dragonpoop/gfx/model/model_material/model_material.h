
#ifndef dragonpoop_model_material_h
#define dragonpoop_model_material_h

#include "../model_component/model_component_type.h"
#include "../model_component/model_component.h"
#include <string>

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
        float shine, opacity;

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
