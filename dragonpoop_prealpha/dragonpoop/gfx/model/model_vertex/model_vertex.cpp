
#include "model_vertex.h"
#include "model_vertex_ref.h"
#include "model_vertex_writelock.h"
#include "model_vertex_readlock.h"

namespace dragonpoop
{

    //ctor
    model_vertex::model_vertex( model_writelock *ml, dpid id ) : model_component( ml, id, model_component_type_vertex, 0 )
    {
        memset( &this->p, 0, sizeof( this->p ) );
    }

    //dtor
    model_vertex::~model_vertex( void )
    {
        model_component_writelock *l;
        shared_obj_guard g;

        l = (model_component_writelock *)g.writeLock( this );
        g.unlock();
    }

    //generate read lock
    shared_obj_readlock *model_vertex::genReadLock( shared_obj *p, dpmutex_readlock *l )
    {
        return new model_vertex_readlock( (model_vertex *)p, l );
    }

    //generate write lock
    shared_obj_writelock *model_vertex::genWriteLock( shared_obj *p, dpmutex_writelock *l )
    {
        return new model_vertex_writelock( (model_vertex *)p, l );
    }

    //generate ref
    shared_obj_ref *model_vertex::genRef( shared_obj *p, std::shared_ptr<shared_obj_refkernal> *k )
    {
        return new model_vertex_ref( (model_vertex *)p, k );
    }

    //do background processing
    void model_vertex::onRun( dpthread_lock *thd, gfx_writelock *g, model_writelock *m, model_component_writelock *l )
    {

    }

    //set position
    void model_vertex::setPosition( dpxyzw *p )
    {
        this->p = *p;
    }

    //get position
    void model_vertex::getPosition( dpxyzw *p )
    {
        *p = this->p;
    }

    //set position
    void model_vertex::setPosition( dpxyzw_f *p )
    {
        p->x = this->p.x;
        p->y = this->p.y;
        p->z = this->p.z;
        p->w = this->p.w;
    }

    //get position
    void model_vertex::getPosition( dpxyzw_f *p )
    {
        this->p.x = p->x;
        this->p.y = p->y;
        this->p.z = p->z;
        this->p.w = p->w;
    }

    //set position
    void model_vertex::setPosition( dpxyz_f *p )
    {
        p->x = this->p.x;
        p->y = this->p.y;
        p->z = this->p.z;
    }

    //get position
    void model_vertex::getPosition( dpxyz_f *p )
    {
        this->p.x = p->x;
        this->p.y = p->y;
        this->p.z = p->z;
        this->p.w = 1.0f;
    }

};
