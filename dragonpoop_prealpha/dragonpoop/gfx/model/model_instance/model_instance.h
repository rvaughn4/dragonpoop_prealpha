
#ifndef dragonpoop_model_instance_h
#define dragonpoop_model_instance_h

#include "../model_component/model_component_type.h"
#include "../model_component/model_component.h"

namespace dragonpoop
{

    class model_instance_ref;
    class model_instance_readlock;
    class model_instance_writelock;
    class model_readlock;
    class model_group_instance_ref;
    class model_triangle_instance_ref;
    class model_triangle_vertex_instance_ref;
    class model_vertex_instance_ref;
    class shared_obj_ref;
    class shared_obj_writelock;

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
        //get triangle instances
        unsigned int getTriangles( std::list<model_triangle_instance_ref *> *l );
        //get triangle instances by group
        unsigned int getTrianglesByGroup( dpid group_id, std::list<model_triangle_instance_ref *> *l );
        //create triangle vertex instances
        void makeTriangleVertexs( dpthread_lock *thd, model_writelock *ml );
        //destroy triangle vertex instances
        void killTriangleVertexs( void );
        //sync traingle vertexs
        void syncTriangleVertexs( model_writelock *ml );
        //get triangle vertex instances
        unsigned int getTriangleVertexs( std::list<model_triangle_vertex_instance_ref *> *l );
        //get triangle vertex instances by triangle
        unsigned int getTriangleVertexsByTriangle( dpid triangle_id, std::list<model_triangle_vertex_instance_ref *> *l );
        //create vertex instances
        void makeVertexs( dpthread_lock *thd, model_writelock *ml );
        //destroy vertex instances
        void killVertexs( void );
        //sync vertexes
        void syncVertexs( model_writelock *ml );
        //get vertex instances
        unsigned int getVertexs( std::list<model_vertex_instance_ref *> *l );
        //returns true if has renderer
        bool hasRenderer( void );
        //set renderer
        void setRenderer( shared_obj_writelock *r );
        //get renderer
        shared_obj_ref *getRenderer( void );

    public:

        //ctor
        model_instance( dpthread_lock *thd, model_writelock *ml, dpid id );
        //dtor
        virtual ~model_instance( void );
        //release list returned by getGroups()
        static void releaseGetGroups( std::list<model_group_instance_ref *> *l );
        //release list returned by getTriangles()
        static void releaseGetTriangles( std::list<model_triangle_instance_ref *> *l );
        //release list returned by getTriangleVertexs()
        static void releaseGetTriangleVertexs( std::list<model_triangle_vertex_instance_ref *> *l );
        //release list returned by getVertexs()
        static void releaseGetVertexs( std::list<model_vertex_instance_ref *> *l );

        friend class model_instance_readlock;
        friend class model_instance_writelock;
    };
    
};

#endif
