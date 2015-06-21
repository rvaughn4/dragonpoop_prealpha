
#ifndef dragonpoop_model_triangle_h
#define dragonpoop_model_triangle_h

#include "../model_component/model_component_type.h"
#include "../model_component/model_component.h"

namespace dragonpoop
{

    class model_triangle_ref;
    class model_triangle_readlock;
    class model_triangle_writelock;
    class model_group_ref;

    class model_triangle : public model_component
    {

    private:

        dpid parent_id;

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

    public:

        //ctor
        model_triangle( model_writelock *ml, dpid id, dpid parent_id );
        //dtor
        virtual ~model_triangle( void );

        friend class model_triangle_readlock;
        friend class model_triangle_writelock;
    };
    
};

#endif
