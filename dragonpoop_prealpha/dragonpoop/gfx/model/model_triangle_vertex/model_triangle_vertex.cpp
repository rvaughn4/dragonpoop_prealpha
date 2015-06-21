
#include "model_triangle_vertex.h"
#include "model_triangle_vertex_ref.h"
#include "model_triangle_vertex_readlock.h"
#include "model_triangle_vertex_writelock.h"

namespace dragonpoop
{

    //ctor
    model_triangle_vertex::model_triangle_vertex( model_writelock *ml, dpid id, dpid triangle_id, dpid vertex_id ) : model_component( ml, id, model_component_type_triangle_vertex, 0 )
    {
        this->vertex_id = vertex_id;
        this->triangle_id = triangle_id;
    }

    //dtor
    model_triangle_vertex::~model_triangle_vertex( void )
    {
        model_component_writelock *l;
        shared_obj_guard g;

        l = (model_component_writelock *)g.writeLock( this );
        g.unlock();
    }

    //generate read lock
    shared_obj_readlock *model_triangle_vertex::genReadLock( shared_obj *p, dpmutex_readlock *l )
    {
        return new model_triangle_vertex_readlock( (model_triangle_vertex *)p, l );
    }

    //generate write lock
    shared_obj_writelock *model_triangle_vertex::genWriteLock( shared_obj *p, dpmutex_writelock *l )
    {
        return new model_triangle_vertex_writelock( (model_triangle_vertex *)p, l );
    }

    //generate ref
    shared_obj_ref *model_triangle_vertex::genRef( shared_obj *p, std::shared_ptr<shared_obj_refkernal> *k )
    {
        return new model_triangle_vertex_ref( (model_triangle_vertex *)p, k );
    }

    //do background processing
    void model_triangle_vertex::onRun( dpthread_lock *thd, gfx_writelock *g, model_writelock *m, model_component_writelock *l )
    {

    }

    //get triangle id
    dpid model_triangle_vertex::getTriangleId( void )
    {
        return this->triangle_id;
    }

    //get triangle
    model_triangle_ref *model_triangle_vertex::getTriangle( void )
    {
        return 0;
    }

    //get vertex id
    dpid model_triangle_vertex::getVertexId( void )
    {
        return this->vertex_id;
    }

    //get vertex
    model_vertex_ref *model_triangle_vertex::getVertex( void )
    {
        return 0;
    }

    //set normal
    void model_triangle_vertex::setNormal( dpxyzw *p )
    {
        this->norm.x = p->x;
        this->norm.y = p->y;
        this->norm.z = p->z;
        this->norm.w = p->w;
    }

    //set normal
    void model_triangle_vertex::setNormal( dpxyzw_f *p )
    {
        this->norm.x = p->x;
        this->norm.y = p->y;
        this->norm.z = p->z;
        this->norm.w = p->w;
    }

    //set normal
    void model_triangle_vertex::setNormal( dpxyz_f *p )
    {
        this->norm.x = p->x;
        this->norm.y = p->y;
        this->norm.z = p->z;
        this->norm.w = 1.0f;
    }

    //get normal
    void model_triangle_vertex::getNormal( dpxyzw *p )
    {
        p->x = this->norm.x;
        p->y = this->norm.y;
        p->z = this->norm.z;
        p->w = this->norm.w;
    }

    //get normal
    void model_triangle_vertex::getNormal( dpxyzw_f *p )
    {
        p->x = this->norm.x;
        p->y = this->norm.y;
        p->z = this->norm.z;
        p->w = this->norm.w;
    }

    //get normal
    void model_triangle_vertex::getNormal( dpxyz_f *p )
    {
        p->x = this->norm.x;
        p->y = this->norm.y;
        p->z = this->norm.z;
    }

    //set texcoord
    void model_triangle_vertex::setTexcoord( uint8_t index, dpst *p )
    {
        if( index > 1 )
            return;
        this->texcoords[ index ].s = p->s;
        this->texcoords[ index ].t = p->t;
    }

    //set texcoord
    void model_triangle_vertex::setTexcoord( uint8_t index, dpst_f *p )
    {
        if( index > 1 )
            return;
        this->texcoords[ index ].s = p->s;
        this->texcoords[ index ].t = p->t;
    }

    //get texcoord
    void model_triangle_vertex::getTexcoord( uint8_t index, dpst *p )
    {
        if( index > 1 )
            return;
        p->s = this->texcoords[ index ].s;
        p->t = this->texcoords[ index ].t;
    }

    //get texcoord
    void model_triangle_vertex::getTexcoord( uint8_t index, dpst_f *p )
    {
        if( index > 1 )
            return;
        p->s = this->texcoords[ index ].s;
        p->t = this->texcoords[ index ].t;
    }

};
