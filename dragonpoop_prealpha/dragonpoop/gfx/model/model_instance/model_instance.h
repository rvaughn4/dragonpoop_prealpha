
#ifndef dragonpoop_model_instance_h
#define dragonpoop_model_instance_h

#include "../model_component/model_component_type.h"
#include "../model_component/model_component.h"

namespace dragonpoop
{

    class shared_obj_ref;
    class shared_obj_writelock;
    class model_instance_ref;
    class model_instance_readlock;
    class model_instance_writelock;
    class model_readlock;
    class model_group_instance_ref;
    class model_triangle_instance_ref;
    class model_animation_instance_ref;
    class model_joint_instance_ref;

    class model_instance : public model_component
    {

    private:

        shared_obj_ref *r;

    protected:

        //generate read lock
        virtual shared_obj_readlock *genReadLock( shared_obj *p, dpmutex_readlock *l );
        //generate write lock
        virtual shared_obj_writelock *genWriteLock( shared_obj *p, dpmutex_writelock *l );
        //generate ref
        virtual shared_obj_ref *genRef( shared_obj *p, std::shared_ptr<shared_obj_refkernal> *k );
        //do background processing
        virtual void onRun( dpthread_lock *thd, gfx_writelock *g, model_writelock *m, model_component_writelock *l );
        //returns true if has renderer
        bool hasRenderer( void );
        //set renderer
        void setRenderer( shared_obj_writelock *r );
        //get renderer
        shared_obj_ref *getRenderer( void );
        //create group instances
        void makeGroups( dpthread_lock *thd, model_writelock *ml );
        //destroy group instances
        void killGroups( void );
        //sync group instances
        void syncGroups( model_writelock *ml );
        //get group instances
        unsigned int getGroups( std::list<model_group_instance_ref *> *l );
        //get group instances by parent
        unsigned int getGroupsByParent( dpid parent_id, std::list<model_group_instance_ref *> *l );
        //create triangle instances
        void makeTriangles( dpthread_lock *thd, model_writelock *ml );
        //destroy triangle instances
        void killTriangles( void );
        //sync triangle instances
        void syncTriangles( model_writelock *ml );
        //get triangle instances
        unsigned int getTriangles( std::list<model_triangle_instance_ref *> *l );
        //get triangle instances by group
        unsigned int getTrianglesByGroup( dpid group_id, std::list<model_triangle_instance_ref *> *l );
        //create animation instances
        void makeAnimations( dpthread_lock *thd, model_writelock *ml );
        //destroy animation instances
        void killAnimations( void );
        //sync animation instances
        void syncAnimations( dpthread_lock *thd, model_writelock *ml );
        //get animation instances
        unsigned int getAnimations( std::list<model_animation_instance_ref *> *l );

        //create joint instances
        void makeJoints( dpthread_lock *thd, model_writelock *ml );
        //destroy joint instances
        void killJoints( void );
        //sync joint instances
        void syncJoints( dpthread_lock *thd, model_writelock *ml );
        //get joint instances
        unsigned int getJoints( std::list<model_joint_instance_ref *> *l );

    public:

        //ctor
        model_instance( dpthread_lock *thd, model_writelock *ml, dpid id );
        //dtor
        virtual ~model_instance( void );
        //release list returned by getGroups()
        static void releaseGetGroups( std::list<model_group_instance_ref *> *l );
        //release list returned by getTriangles()
        static void releaseGetTriangles( std::list<model_triangle_instance_ref *> *l );
        //release list returned by getAnimations()
        static void releaseGetAnimations( std::list<model_animation_instance_ref *> *l );
        //release list returned by getJoints()
        static void releaseGetJoints( std::list<model_joint_instance_ref *> *l );

        friend class model_instance_readlock;
        friend class model_instance_writelock;
    };
    
};

#endif
