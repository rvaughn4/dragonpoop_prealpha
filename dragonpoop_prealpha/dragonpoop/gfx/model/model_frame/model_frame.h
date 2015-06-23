
#ifndef dragonpoop_model_frame_h
#define dragonpoop_model_frame_h

#include "../model_component/model_component_type.h"
#include "../model_component/model_component.h"
#include <string>

namespace dragonpoop
{

    class model_frame_ref;
    class model_frame_readlock;
    class model_frame_writelock;

    class model_frame : public model_component
    {

    private:

        std::string sname;

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

    public:

        //ctor
        model_frame( model_writelock *ml, dpid id );
        //dtor
        virtual ~model_frame( void );

        friend class model_frame_readlock;
        friend class model_frame_writelock;
    };
    
};

#endif
