
#ifndef dragonpoop_model_triangle_vertex_h
#define dragonpoop_model_triangle_vertex_h

#include "../model_component/model_component_type.h"
#include "../model_component/model_component.h"
#include "../../dpvertex/dpvertexes.h"

namespace dragonpoop
{

    class model_triangle_vertex_ref;
    class model_triangle_vertex_readlock;
    class model_triangle_vertex_writelock;
    class model_triangle_ref;
    class model_vertex_ref;

    class model_triangle_vertex : public model_component
    {

    private:

        dpid triangle_id, vertex_id;
        dpxyzw norm;
        dpst texcoords[ 2 ];

    protected:

        //generate read lock
        virtual shared_obj_readlock *genReadLock( shared_obj *p, dpmutex_readlock *l );
        //generate write lock
        virtual shared_obj_writelock *genWriteLock( shared_obj *p, dpmutex_writelock *l );
        //generate ref
        virtual shared_obj_ref *genRef( shared_obj *p, std::shared_ptr<shared_obj_refkernal> *k );
        //do background processing
        virtual void onRun( dpthread_lock *thd, gfx_writelock *g, model_writelock *m, model_component_writelock *l );
        //get triangle id
        dpid getTriangleId( void );
        //get triangle
        model_triangle_ref *getTriangle( void );
        //get vertex id
        dpid getVertexId( void );
        //get vertex
        model_vertex_ref *getVertex( void );
        //set normal
        void setNormal( dpxyzw *p );
        //set normal
        void setNormal( dpxyzw_f *p );
        //set normal
        void setNormal( dpxyz_f *p );
        //get normal
        void getNormal( dpxyzw *p );
        //get normal
        void getNormal( dpxyzw_f *p );
        //get normal
        void getNormal( dpxyz_f *p );
        //set texcoord
        void setTexcoord( uint8_t index, dpst *p );
        //set texcoord
        void setTexcoord( uint8_t index, dpst_f *p );
        //get texcoord
        void getTexcoord( uint8_t index, dpst *p );
        //get texcoord
        void getTexcoord( uint8_t index, dpst_f *p );

    public:

        //ctor
        model_triangle_vertex( model_writelock *ml, dpid id, dpid triangle_id, dpid vertex_id );
        //dtor
        virtual ~model_triangle_vertex( void );

        friend class model_triangle_vertex_readlock;
        friend class model_triangle_vertex_writelock;
    };
    
};

#endif
