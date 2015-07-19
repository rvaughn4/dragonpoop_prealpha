
#ifndef dragonpoop_model_group_h
#define dragonpoop_model_group_h

#include "../model_component/model_component_type.h"
#include "../model_component/model_component.h"
#include <string>

namespace dragonpoop
{

    class model_group_ref;
    class model_group_readlock;
    class model_group_writelock;

    class model_group : public model_component
    {

    private:

        std::string sname;
        dpid parent_id, material_id;

    protected:

        //generate read lock
        virtual shared_obj_readlock *genReadLock( shared_obj *p, dpmutex_readlock *l );
        //generate write lock
        virtual shared_obj_writelock *genWriteLock( shared_obj *p, dpmutex_writelock *l );
        //generate ref
        virtual shared_obj_ref *genRef( shared_obj *p, std::shared_ptr<shared_obj_refkernal> *k );
        //do background processing
        virtual void onRun( dpthread_lock *thd, gfx_writelock *g, model_writelock *m, model_component_writelock *l );
        //get parent id
        dpid getParentId( void );
        //get parent
        model_group_ref *getParent( void );
        //get name
        void getName( std::string *s );
        //set name
        void setName( std::string *s );
        //set material id
        void setMaterialId( dpid id );
        //get material id
        dpid getMaterialId( void );
        //returns true if has material
        bool hasMaterial( void );

    public:

        //ctor
        model_group( model_writelock *ml, dpid id, dpid parent_id );
        //dtor
        virtual ~model_group( void );

        friend class model_group_readlock;
        friend class model_group_writelock;
    };
    
};

#endif
