
#ifndef dragonpoop_model_instance_readlock_h
#define dragonpoop_model_instance_readlock_h

#include "../model_component/model_component_readlock.h"
#include <list>

namespace dragonpoop
{

    class model_instance;
    class model_instance_ref;
    class model_group_instance_ref;
    class model_triangle_instance_ref;
    class model_triangle_vertex_instance_ref;

    class model_instance_readlock : public model_component_readlock
    {

    private:

        model_instance *t;

    protected:

        //ctor
        model_instance_readlock( model_instance *t, dpmutex_readlock *l );
        //dtor
        virtual ~model_instance_readlock( void );

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

        friend class model_instance;
    };
    
};

#endif