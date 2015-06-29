
#ifndef dragonpoop_model_joint_h
#define dragonpoop_model_joint_h

#include "../model_component/model_component_type.h"
#include "../model_component/model_component.h"
#include "../../dpvertex/dpvertexes.h"
#include <string>

namespace dragonpoop
{

    class model_joint_ref;
    class model_joint_readlock;
    class model_joint_writelock;

    class model_joint : public model_component
    {

    private:

        dpxyzw pos, rot;
        std::string sname;
        dpid pid;

    protected:

        //generate read lock
        virtual shared_obj_readlock *genReadLock( shared_obj *p, dpmutex_readlock *l );
        //generate write lock
        virtual shared_obj_writelock *genWriteLock( shared_obj *p, dpmutex_writelock *l );
        //generate ref
        virtual shared_obj_ref *genRef( shared_obj *p, std::shared_ptr<shared_obj_refkernal> *k );
        //do background processing
        virtual void onRun( dpthread_lock *thd, gfx_writelock *g, model_writelock *m, model_component_writelock *l );
        //get position
        void getPosition( dpxyzw *p );
        //get roatation
        void getRotation( dpxyzw *p );
        //get name
        void getName( std::string *s );
        //set position
        void setPosition( dpxyzw *p );
        //set roatation
        void setRotation( dpxyzw *p );
        //set name
        void setName( std::string *s );
        //return parent id
        dpid getParentId( void );
        //return parent
        model_joint_ref *getParent( void );

    public:

        //ctor
        model_joint( model_writelock *ml, dpid id, dpid pid );
        //dtor
        virtual ~model_joint( void );

        friend class model_joint_readlock;
        friend class model_joint_writelock;
    };
    
};

#endif
