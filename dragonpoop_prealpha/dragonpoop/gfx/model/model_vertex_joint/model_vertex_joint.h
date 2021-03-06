
#ifndef dragonpoop_model_vertex_joint_h
#define dragonpoop_model_vertex_joint_h

#include "../model_component/model_component_type.h"
#include "../model_component/model_component.h"

namespace dragonpoop
{

    class model_vertex_joint_ref;
    class model_vertex_joint_readlock;
    class model_vertex_joint_writelock;
    class model_joint_ref;
    class model_vertex_ref;

    class model_vertex_joint : public model_component
    {

    private:

        dpid joint_id, vertex_id;
        float weight;

    protected:

        //generate read lock
        virtual shared_obj_readlock *genReadLock( shared_obj *p, dpmutex_readlock *l );
        //generate write lock
        virtual shared_obj_writelock *genWriteLock( shared_obj *p, dpmutex_writelock *l );
        //generate ref
        virtual shared_obj_ref *genRef( shared_obj *p, std::shared_ptr<shared_obj_refkernal> *k );
        //do background processing
        virtual void onRun( dpthread_lock *thd, gfx_writelock *g, model_writelock *m, model_component_writelock *l );
        //returns joint id
        dpid getJointId( void );
        //returns joint
        model_joint_ref *getJoint( void );
        //returns vertex id
        dpid getVertexId( void );
        //returns vertex
        model_vertex_ref *getVertex( void );
        //returns weight
        float getWeight( void );
        //sets weight
        void setWeight( float w );

    public:

        //ctor
        model_vertex_joint( model_writelock *ml, dpid id, dpid vertex_id, dpid joint_id );
        //dtor
        virtual ~model_vertex_joint( void );

        friend class model_vertex_joint_readlock;
        friend class model_vertex_joint_writelock;
    };
    
};

#endif
