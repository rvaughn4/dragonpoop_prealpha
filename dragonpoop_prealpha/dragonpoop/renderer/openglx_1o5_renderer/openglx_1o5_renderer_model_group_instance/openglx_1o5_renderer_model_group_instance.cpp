
#include "openglx_1o5_renderer_model_group_instance.h"
#include "openglx_1o5_renderer_model_group_instance_writelock.h"
#include "openglx_1o5_renderer_model_group_instance_readlock.h"
#include "openglx_1o5_renderer_model_group_instance_ref.h"
#include "../openglx_1o5_renderer_writelock.h"
#include "../openglx_1o5_renderer_ref.h"

namespace dragonpoop
{

    //ctor
    openglx_1o5_renderer_model_group_instance::openglx_1o5_renderer_model_group_instance( gfx_writelock *g, openglx_1o5_renderer_writelock *r, model_instance_writelock *m, model_group_instance_writelock *grp ) : renderer_model_group_instance( g, r, m, grp )
    {
        this->r = (openglx_1o5_renderer_ref *)r->getRef();
    }

    //dtor
    openglx_1o5_renderer_model_group_instance::~openglx_1o5_renderer_model_group_instance( void )
    {
        delete this->r;
    }

    //generate read lock
    shared_obj_readlock *openglx_1o5_renderer_model_group_instance::genReadLock( shared_obj *p, dpmutex_readlock *l )
    {
        return new openglx_1o5_renderer_model_group_instance_readlock( (openglx_1o5_renderer_model_group_instance *)p, l );
    }

    //generate write lock
    shared_obj_writelock *openglx_1o5_renderer_model_group_instance::genWriteLock( shared_obj *p, dpmutex_writelock *l )
    {
        return new openglx_1o5_renderer_model_group_instance_writelock( (openglx_1o5_renderer_model_group_instance *)p, l );
    }

    //generate ref
    shared_obj_ref *openglx_1o5_renderer_model_group_instance::genRef( shared_obj *p, std::shared_ptr<shared_obj_refkernal> *k )
    {
        return new openglx_1o5_renderer_model_group_instance_ref( (openglx_1o5_renderer_model_group_instance *)p, k );
    }

    //called after run
    void openglx_1o5_renderer_model_group_instance::onRun( dpthread_lock *thd, openglx_1o5_renderer_model_instance_writelock *m, openglx_1o5_renderer_model_group_instance_writelock *grp, openglx_1o5_renderer_writelock *r )
    {

    }

    //called after sync
    void openglx_1o5_renderer_model_group_instance::onSync( dpthread_lock *thd, openglx_1o5_renderer_model_instance_writelock *m, openglx_1o5_renderer_model_group_instance_writelock *grp, openglx_1o5_renderer_writelock *r )
    {

    }

};
