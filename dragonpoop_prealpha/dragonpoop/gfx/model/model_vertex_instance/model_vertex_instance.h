
#ifndef dragonpoop_model_vertex_instance_h
#define dragonpoop_model_vertex_instance_h

#include "../model_component/model_component_type.h"
#include "../model_component/model_component.h"

namespace dragonpoop
{

    class model_vertex_instance_ref;
    class model_vertex_instance_readlock;
    class model_vertex_instance_writelock;

    class model_vertex_instance : public model_component
    {

    private:

    protected:

        //generate read lock
        virtual shared_obj_readlock *genReadLock( shared_obj *p, dpmutex_readlock *l );
        //generate write lock
        virtual shared_obj_writelock *genWriteLock( shared_obj *p, dpmutex_writelock *l );
        //generate ref
        virtual shared_obj_ref *genRef( shared_obj *p, std::shared_ptr<shared_obj_refkernal> *k );
        //do background processing
        virtual void onRun( dpthread_lock *thd, gfx_writelock *g, model_writelock *m, model_component_writelock *l );

    public:

        //ctor
        model_vertex_instance( model_writelock *ml, dpid id );
        //dtor
        virtual ~model_vertex_instance( void );

        friend class model_vertex_instance_readlock;
        friend class model_vertex_instance_writelock;
    };
    
};

#endif
