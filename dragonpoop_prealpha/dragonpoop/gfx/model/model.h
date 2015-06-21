
#ifndef dragonpoop_model_h
#define dragonpoop_model_h

#include "../../core/shared_obj/shared_obj.h"
#include "../../core/dpid/dpid.h"
#include <string>

namespace dragonpoop
{

    class core;
    class gfx_writelock;
    class gfx_ref;
    class dpthread_lock;
    class model_writelock;
    class model_component;
    class model_component_ref;
    class model_component_tree_byid;
    class model_component_tree_bytype;
    class model_component_tree_byidtype;
    class model_component_tree_byowner;
    class model_component_tree_byownertype;
    class model_vertex;
    class model_vertex_ref;
    class model_group_ref;
    class model_group;
    class model_triangle_ref;
    class model_triangle;
    class model_triangle_vertex_ref;
    class model_triangle_vertex;

    class model : public shared_obj
    {

    private:

        core *c;
        gfx_ref *g;
        std::string sname;
        dpid id;
        bool bAlive;

        struct
        {
            std::list<model_component *> lst;
            model_component_tree_byid *byid;
            model_component_tree_bytype *bytype;
            model_component_tree_byidtype *byidtype;
            model_component_tree_byowner *byowner;
            model_component_tree_byownertype *byownertype;
        } comps;

    protected:

        //generate read lock
        virtual shared_obj_readlock *genReadLock( shared_obj *p, dpmutex_readlock *l );
        //generate write lock
        virtual shared_obj_writelock *genWriteLock( shared_obj *p, dpmutex_writelock *l );
        //generate ref
        virtual shared_obj_ref *genRef( shared_obj *p, std::shared_ptr<shared_obj_refkernal> *k );
        //set name
        void setName( std::string *s );
        //set name
        void setName( const char *c );
        //get name
        void getName( std::string *s );
        //set id
        void setId( dpid id );
        //get id
        dpid getId( void );
        //kill model
        void kill( void );
        //run model
        void run( dpthread_lock *thd, gfx_writelock *g, model_writelock *m );
        //run model components
        void runComps( dpthread_lock *thd, gfx_writelock *g, model_writelock *m );
        //delete model components
        void deleteComps( void );
        //add new comp
        void addComp( model_component *c, dpid id, uint16_t ctype );
        //add new comp
        void addComp( model_component *c, dpid id, uint16_t ctype, dpid parent_0 );
        //add new comp
        void addComp( model_component *c, dpid id, uint16_t ctype, dpid parent_0, dpid parent_1 );
        //find model component by id
        model_component_ref *find( dpid id );
        //find model component by id and type
        model_component_ref *find( dpid id, uint16_t ctype );
        //get components by type
        unsigned int getComponentsByType( std::list<model_component_ref *> *l, uint16_t ctype );
        //get components by owner
        unsigned int getComponentsByOwner( std::list<model_component_ref *> *l, dpid id );
        //get components by owner and type
        unsigned int getComponentsByOwnerAndType( std::list<model_component_ref *> *l, dpid id, uint16_t ctype );
        //create a list of comp refs from list of components
        static void createComponentRefs( std::list<model_component *> *l, std::list<model_component_ref *> *lr );
        //release list retured by getComponents()
        static void releaseGetComponents( std::list<model_component_ref *> *l );
        //create a vertex
        model_vertex_ref *createVertex( dpthread_lock *thd, model_writelock *m );
        //find a vertex by id
        model_vertex_ref *findVertex( dpid id );
        //get all vertexes
        unsigned int getVertexes( std::list<model_vertex_ref *> *l );
        //release list returned by getVertexes()
        static void releaseGetVertexes( std::list<model_vertex_ref *> *l );
        //create a group
        model_group_ref *createGroup( dpthread_lock *thd, model_writelock *m );
        //create a group
        model_group_ref *createGroup( dpthread_lock *thd, model_writelock *m, dpid parent_id );
        //find a group by id
        model_group_ref *findGroup( dpid id );
        //get all groups
        unsigned int getGroups( std::list<model_group_ref *> *l );
        //get all groups belonging to parent
        unsigned int getGroupsByParent( std::list<model_group_ref *> *l, dpid parent_id );
        //release list returned by getGroups()
        static void releaseGetGroups( std::list<model_group_ref *> *l );
        //create a triangle
        model_triangle_ref *createTriangle( dpthread_lock *thd, model_writelock *m, dpid group_id );
        //find a triangle by id
        model_triangle_ref *findTriangle( dpid id );
        //get all triangles
        unsigned int getTriangles( std::list<model_triangle_ref *> *l );
        //get all triangles belonging to group
        unsigned int getTrianglesByGroup( std::list<model_triangle_ref *> *l, dpid group_id );
        //release list returned by getTriangles()
        static void releaseGetTriangles( std::list<model_triangle_ref *> *l );
        //create a triangle vertex
        model_triangle_vertex_ref *createTriangleVertex( dpthread_lock *thd, model_writelock *m, dpid triangle_id, dpid vertex_id );
        //find a triangle vertex by id
        model_triangle_vertex_ref *findTriangleVertex( dpid id );
        //get all triangle vertexes
        unsigned int getTriangleVertexes( std::list<model_triangle_vertex_ref *> *l );
        //get all triangle vertexes belonging to triangle
        unsigned int getTriangleVertexesByTriangle( std::list<model_triangle_vertex_ref *> *l, dpid triangle_id );
        //get all triangle vertexes belonging to vertex
        unsigned int getTriangleVertexesByVertex( std::list<model_triangle_vertex_ref *> *l, dpid vertex_id );
        //release list returned by getTriangleVertexes()
        static void releaseGetTriangleVertexes( std::list<model_triangle_vertex_ref *> *l );
        //clear all components from model
        void clear( void );

    public:

        //ctor
        model( gfx_writelock *g, dpid id, const char *cname );
        //dtor
        virtual ~model( void );
        //return core
        core *getCore( void );
        //returns true if alive
        bool isAlive( void );

        friend class model_readlock;
        friend class model_writelock;
    };
    
};

#endif