
#ifndef dragonpoop_renderer_model_group_instance_h
#define dragonpoop_renderer_model_group_instance_h

#include "../../core/shared_obj/shared_obj.h"
#include "../../core/dpid/dpid.h"
#include "../../gfx/dpvertex/dpvertexes.h"

namespace dragonpoop
{

    class core;
    class gfx_writelock;
    class gfx_ref;
    class dpthread_lock;
    class renderer_model_group_instance_ref;
    class renderer_model_group_instance_readlock;
    class renderer_model_group_instance_writelock;
    class renderer_ref;
    class renderer_writelock;
    class model_group_instance_ref;
    class model_group_instance_writelock;
    class renderer_model_instance_writelock;
    class renderer_model_instance_readlock;
    class model_instance_ref;
    class model_instance_readlock;
    class model_instance_writelock;

    class renderer_model_group_instance : public shared_obj
    {

    private:

        core *c;
        gfx_ref *g;
        dpid id, instance_id, parent_id;
        bool bAlive;
        renderer_ref *r;
        model_group_instance_ref *grp;
        model_instance_ref *m;
        bool beenAssetSynced;
        std::list<renderer_model_group_instance *> groups;
        dpvertexindex_buffer vb;

    protected:

        //generate read lock
        virtual shared_obj_readlock *genReadLock( shared_obj *p, dpmutex_readlock *l );
        //generate write lock
        virtual shared_obj_writelock *genWriteLock( shared_obj *p, dpmutex_writelock *l );
        //generate ref
        virtual shared_obj_ref *genRef( shared_obj *p, std::shared_ptr<shared_obj_refkernal> *k );
        //get id
        dpid getId( void );
        //kill model
        void kill( void );
        //run group
        void run( dpthread_lock *thd, renderer_model_instance_writelock *m, renderer_model_group_instance_writelock *grp, renderer_writelock *r );
        //sync group
        void sync( dpthread_lock *thd, renderer_model_instance_writelock *m, renderer_model_group_instance_writelock *grp, renderer_writelock *r );
        //render group
        void render( dpthread_lock *thd, renderer_model_instance_readlock *m, renderer_model_group_instance_readlock *grp, renderer_writelock *r );
        //return instance id
        dpid getInstanceId( void );
        //generate group from renderer
        renderer_model_group_instance *genGroup( gfx_writelock *g, renderer_writelock *r, model_instance_writelock *m, model_group_instance_writelock *grp );
        //sync assets like groups and materials
        void syncAssets( gfx_writelock *g, renderer_model_instance_writelock *m, renderer_model_group_instance_writelock *gl, renderer_writelock *r, model_group_instance_writelock *grp );
        //make groups
        void makeGroups( gfx_writelock *g, renderer_model_instance_writelock *m, renderer_writelock *r, model_group_instance_writelock *grp );
        //kill groups
        void killGroups( renderer_model_instance_writelock *m, renderer_writelock *r );
        //run groups
        void runGroups( dpthread_lock *thd, renderer_model_instance_writelock *m, renderer_writelock *r );
        //sync groups
        void syncGroups( dpthread_lock *thd, renderer_model_instance_writelock *m, renderer_writelock *r );
        //render groups
        void renderGroups( dpthread_lock *thd, renderer_model_instance_readlock *m, renderer_writelock *r );
        //returns pointer to vertex buffer
        dpvertexindex_buffer *getBuffer( void );

    public:

        //ctor
        renderer_model_group_instance( gfx_writelock *g, renderer_writelock *r, model_instance_writelock *m, model_group_instance_writelock *grp );
        //dtor
        virtual ~renderer_model_group_instance( void );
        //return core
        core *getCore( void );
        //returns true if alive
        bool isAlive( void );

        friend class renderer_model_group_instance_readlock;
        friend class renderer_model_group_instance_writelock;
    };
    
};

#endif