
#ifndef dragonpoop_model_readlock_h
#define dragonpoop_model_readlock_h

#include "../../core/shared_obj/shared_obj_readlock.h"
#include "../../core/dpid/dpid.h"
#include <string>
#include <list>

namespace dragonpoop
{
    class model;
    class core;
    class model_vertex_ref;
    class model_group_ref;
    class model_triangle_ref;
    class model_triangle_vertex_ref;
    class model_material_ref;
    class model_animation_ref;
    class model_frame_ref;
    class model_animation_frame_ref;
    class model_frame_joint_ref;
    class model_joint_ref;
    class model_vertex_joint_ref;

    class model_readlock : public shared_obj_readlock
    {

    private:

        model *t;

    protected:

        //ctor
        model_readlock( model *t, dpmutex_readlock *l );
        //dtor
        virtual ~model_readlock( void );

    public:

        //return core
        core *getCore( void );
        //get name
        void getName( std::string *s );
        //get id
        dpid getId( void );
        //returns true if alive
        bool isAlive( void );
        //get all vertexes
        unsigned int getVertexes( std::list<model_vertex_ref *> *l );
        //release list returned by getVertexes()
        void releaseGetVertexes( std::list<model_vertex_ref *> *l );
        //find a vertex by id
        model_vertex_ref *findVertex( dpid id );
        //find a group by id
        model_group_ref *findGroup( dpid id );
        //get all groups
        unsigned int getGroups( std::list<model_group_ref *> *l );
        //get all groups by parent
        unsigned int getGroupsByParent( std::list<model_group_ref *> *l, dpid parent_id );
        //release list returned by getGroups()
        void releaseGetGroups( std::list<model_group_ref *> *l );
        //find a triangle by id
        model_triangle_ref *findTriangle( dpid id );
        //get all triangles
        unsigned int getTriangles( std::list<model_triangle_ref *> *l );
        //get all triangles belonging to group
        unsigned int getTrianglesByGroup( std::list<model_triangle_ref *> *l, dpid group_id );
        //release list returned by getTriangles()
        void releaseGetTriangles( std::list<model_triangle_ref *> *l );
        //find a triangle vertex by id
        model_triangle_vertex_ref *findTriangleVertex( dpid id );
        //get all triangle vertexes
        unsigned int getTriangleVertexes( std::list<model_triangle_vertex_ref *> *l );
        //get all triangle vertexes belonging to triangle
        unsigned int getTriangleVertexesByTriangle( std::list<model_triangle_vertex_ref *> *l, dpid triangle_id );
        //get all triangle vertexes belonging to vertex
        unsigned int getTriangleVertexesByVertex( std::list<model_triangle_vertex_ref *> *l, dpid vertex_id );
        //release list returned by getTriangleVertexes()
        void releaseGetTriangleVertexes( std::list<model_triangle_vertex_ref *> *l );
        //find a material by id
        model_material_ref *findMaterial( dpid id );
        //get all materials
        unsigned int getMaterials( std::list<model_material_ref *> *l );
        //release list returned by getMateriales()
        void releaseGetMaterials( std::list<model_material_ref *> *l );
        //find a animation by id
        model_animation_ref *findAnimation( dpid id );
        //get all animations
        unsigned int getAnimations( std::list<model_animation_ref *> *l );
        //release list returned by getAnimations()
        void releaseGetAnimations( std::list<model_animation_ref *> *l );
        //find a Frame by id
        model_frame_ref *findFrame( dpid id );
        //get all Frames
        unsigned int getFrames( std::list<model_frame_ref *> *l );
        //release list returned by getFrames()
        static void releaseGetFrames( std::list<model_frame_ref *> *l );
        //find a animation_frame by id
        model_animation_frame_ref *findAnimationFrame( dpid id );
        //get all animation_frames
        unsigned int getAnimationFrames( std::list<model_animation_frame_ref *> *l );
        //release list returned by getAnimationFrames()
        void releaseGetAnimationFrames( std::list<model_animation_frame_ref *> *l );
        //find a frame joint by id
        model_frame_joint_ref *findFrameJoint( dpid id );
        //get all frame joints
        unsigned int getFrameJoints( std::list<model_frame_joint_ref *> *l );
        //release list returned by getFrameJoints()
        void releaseGetFrameJoints( std::list<model_frame_joint_ref *> *l );
        //find a joint by id
        model_joint_ref *findJoint( dpid id );
        //get all frame joints
        unsigned int getJoints( std::list<model_joint_ref *> *l );
        //release list returned by getFrameJoints()
        void releaseGetJoints( std::list<model_joint_ref *> *l );
        //find a vertex joint by id
        model_vertex_joint_ref *findVertexJoint( dpid id );
        //get all vertex joints
        unsigned int getVertexJoints( std::list<model_vertex_joint_ref *> *l );
        //release list returned by getVertexJoints()
        void releaseGetVertexJoints( std::list<model_vertex_joint_ref *> *l );

        friend class model;
    };
    
};

#endif