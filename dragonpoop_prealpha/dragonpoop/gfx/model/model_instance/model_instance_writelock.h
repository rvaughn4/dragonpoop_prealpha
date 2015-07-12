
#ifndef dragonpoop_model_instance_writelock_h
#define dragonpoop_model_instance_writelock_h

#include "../model_component/model_component_writelock.h"
#include <list>

namespace dragonpoop
{

    class model_instance;
    class model_instance_ref;
    class model_group_instance_ref;
    class model_triangle_instance_ref;
    class model_triangle_vertex_instance_ref;
    class model_vertex_instance_ref;

    class model_instance_writelock : public model_component_writelock
    {

    private:

        model_instance *t;

    protected:

        //ctor
        model_instance_writelock( model_instance *t, dpmutex_writelock *l );
        //dtor
        virtual ~model_instance_writelock( void );

    public:

        //get group instances
        unsigned int getGroups( std::list<model_group_instance_ref *> *l );
        //get group instances by parent
        unsigned int getGroupsByParent( dpid parent_id, std::list<model_group_instance_ref *> *l );
        //release list returned by getGroups()
        void releaseGetGroups( std::list<model_group_instance_ref *> *l );
        //get triangle instances
        unsigned int getTriangles( std::list<model_triangle_instance_ref *> *l );
        //get triangle instances by group
        unsigned int getTrianglesByGroup( dpid group_id, std::list<model_triangle_instance_ref *> *l );
        //release list returned by getTriangles()
        void releaseGetTriangles( std::list<model_triangle_instance_ref *> *l );
        //get triangle vertex instances
        unsigned int getTriangleVertexs( std::list<model_triangle_vertex_instance_ref *> *l );
        //get triangle vertex instances by triangle
        unsigned int getTriangleVertexsByTriangle( dpid triangle_id, std::list<model_triangle_vertex_instance_ref *> *l );
        //release list returned by getTriangleVertexs()
        void releaseGetTriangleVertexs( std::list<model_triangle_vertex_instance_ref *> *l );
        //get vertex instances
        unsigned int getVertexs( std::list<model_vertex_instance_ref *> *l );
        //release list returned by getVertexs()
        void releaseGetVertexs( std::list<model_vertex_instance_ref *> *l );
        //returns true if has renderer
        bool hasRenderer( void );
        //set renderer
        void setRenderer( shared_obj_writelock *r );
        //get renderer
        shared_obj_ref *getRenderer( void );

        friend class model_instance;
    };
    
};

#endif