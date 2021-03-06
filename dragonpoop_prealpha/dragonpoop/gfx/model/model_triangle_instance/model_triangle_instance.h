
#ifndef dragonpoop_model_triangle_instance_h
#define dragonpoop_model_triangle_instance_h

#include "../model_component/model_component_type.h"
#include "../model_component/model_component.h"
#include "../../dpvertex/dpvertexes.h"

namespace dragonpoop
{

    class model_triangle_instance_ref;
    class model_triangle_instance_readlock;
    class model_triangle_instance_writelock;
    class dpvertexindex_buffer;
    class model_writelock;
    class model_vertex_joint_readlock;

    struct model_triangle_instance_vert
    {
        dpid vertex_id, triagnle_vertex_id, joint_id;
        dpvertex orig_data, trans_data;
    };

    class model_triangle_instance : public model_component
    {

    private:

        dpid instance_id, triangle_id, group_id;
        model_triangle_instance_vert vert[ 3 ];
        bool isLoaded;

        //apply joints to vertex
        void applyJoints( model_writelock *ml, model_triangle_instance_vert *p );
        //accumulate joint transforms
        void accumJoint( model_writelock *ml, model_vertex_joint_readlock *j, dpxyzw *ptrans, dpxyzw *prot, float *pw );

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
        //return group id
        dpid getGroupId( void );
        //get vertexes
        void getVertexes( model_writelock *ml, dpvertexindex_buffer *b );
        //sync triangle
        void sync( model_writelock *ml );

    public:

        //ctor
        model_triangle_instance( model_writelock *ml, dpid id, dpid instance_id, dpid triangle_id, dpid group_id );
        //dtor
        virtual ~model_triangle_instance( void );

        friend class model_triangle_instance_readlock;
        friend class model_triangle_instance_writelock;
    };
    
};

#endif
