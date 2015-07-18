
#ifndef dragonpoop_model_triangle_vertex_instance_h
#define dragonpoop_model_triangle_vertex_instance_h

#include "../model_component/model_component_type.h"
#include "../model_component/model_component.h"
#include "../../dpvertex/dpvertexes.h"

namespace dragonpoop
{

    class model_triangle_vertex_instance_ref;
    class model_triangle_vertex_instance_readlock;
    class model_triangle_vertex_instance_writelock;
    class dpvertexindex_buffer;

    class model_triangle_vertex_instance : public model_component
    {

    private:

        dpid instance_id, triangle_id, vertex_id, triangle_vertex_id;
        dpxyzw norm[ 2 ];
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
        //return instance id
        dpid getInstanceId( void );
        //return triangle id
        dpid getTriangleId( void );
        //return vertex id
        dpid getVertexId( void );
        //return triangle vertex id
        dpid getTriangleVertexId( void );
        //get vertexes
        void getVertex( dpvertexindex_buffer *b );
        //sync vertex
        void sync( void );

    public:

        //ctor
        model_triangle_vertex_instance( model_writelock *ml, dpid id, dpid instance_id, dpid traingle_vertex_id, dpid triangle_id, dpid vertex_id );
        //dtor
        virtual ~model_triangle_vertex_instance( void );

        friend class model_triangle_vertex_instance_readlock;
        friend class model_triangle_vertex_instance_writelock;
    };
    
};

#endif
