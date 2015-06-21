
#ifndef dragonpoop_model_vertex_h
#define dragonpoop_model_vertex_h

#include "../model_component/model_component_type.h"
#include "../model_component/model_component.h"
#include "../../dpvertex/dpxyzw.h"
#include "../../dpvertex/dpxyzw_f.h"
#include "../../dpvertex/dpxyz_f.h"

namespace dragonpoop
{

    class model_vertex : public model_component
    {

    private:

        dpxyzw p;

    protected:

        //generate read lock
        virtual shared_obj_readlock *genReadLock( shared_obj *p, dpmutex_readlock *l );
        //generate write lock
        virtual shared_obj_writelock *genWriteLock( shared_obj *p, dpmutex_writelock *l );
        //generate ref
        virtual shared_obj_ref *genRef( shared_obj *p, std::shared_ptr<shared_obj_refkernal> *k );
        //do background processing
        virtual void onRun( dpthread_lock *thd, gfx_writelock *g, model_writelock *m, model_component_writelock *l );
        //set position
        void setPosition( dpxyzw *p );
        //get position
        void getPosition( dpxyzw *p );
        //set position
        void setPosition( dpxyzw_f *p );
        //get position
        void getPosition( dpxyzw_f *p );
        //set position
        void setPosition( dpxyz_f *p );
        //get position
        void getPosition( dpxyz_f *p );

    public:

        //ctor
        model_vertex( model_writelock *ml, dpid id );
        //dtor
        virtual ~model_vertex( void );

        friend class model_vertex_readlock;
        friend class model_vertex_writelock;
    };
    
};

#endif
