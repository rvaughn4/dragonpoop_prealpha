
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
    class model_instance_ref;
    class model_group_instance_ref;
    class model_triangle_instance_ref;
    class model_triangle_vertex_instance_ref;
    class model_vertex_instance_ref;

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
        //get all animation_frames by animation id
        unsigned int getAnimationFramesByAnimation( std::list<model_animation_frame_ref *> *l, dpid anim_id );
        //release list returned by getAnimationFrames()
        void releaseGetAnimationFrames( std::list<model_animation_frame_ref *> *l );
        //find a frame joint by id
        model_frame_joint_ref *findFrameJoint( dpid id );
        //get all frame joints
        unsigned int getFrameJoints( std::list<model_frame_joint_ref *> *l );
        //get all frame joints by frame id
        unsigned int getFrameJointsByFrame( std::list<model_frame_joint_ref *> *l, dpid frame_id );
        //get all frame joints by joint id
        unsigned int getFrameJointsByJoint( std::list<model_frame_joint_ref *> *l, dpid joint_id );
        //get all frame joints by joint and frame id
        unsigned int getFrameJointsByFrameAndJoint( std::list<model_frame_joint_ref *> *l, dpid frame_id, dpid joint_id );
        //release list returned by getFrameJoints()
        void releaseGetFrameJoints( std::list<model_frame_joint_ref *> *l );
        //find a joint by id
        model_joint_ref *findJoint( dpid id );
        //get all joints
        unsigned int getJoints( std::list<model_joint_ref *> *l );
        //get all joints by parent id
        unsigned int getJointsByParent( std::list<model_joint_ref *> *l, dpid parent_id );
        //release list returned by getFrameJoints()
        void releaseGetJoints( std::list<model_joint_ref *> *l );
        //find a vertex joint by id
        model_vertex_joint_ref *findVertexJoint( dpid id );
        //get all vertex joints
        unsigned int getVertexJoints( std::list<model_vertex_joint_ref *> *l );
        //get all vertex joints by vertex
        unsigned int getVertexJointsByVertex( std::list<model_vertex_joint_ref *> *l, dpid vertex_id );
        //get all vertex joints by joint
        unsigned int getVertexJointsByJoint( std::list<model_vertex_joint_ref *> *l, dpid joint_id );
        //release list returned by getVertexJoints()
        void releaseGetVertexJoints( std::list<model_vertex_joint_ref *> *l );
        //returns default animation id
        dpid getDefaultAnimationId( void );
        //returns default animation
        model_animation_ref *getDefaultAnimation( void );
        //set default animation id
        void setDefaultAnimationId( dpid id );
        //find model instance
        model_instance_ref *findInstance( dpid id );
        //get model instances
        unsigned int getInstances( std::list<model_instance_ref *> *l );
        //release list returned by getInstances()
        void releaseGetInstances( std::list<model_instance_ref *> *l );
        //find group instance
        model_group_instance_ref *findGroupInstance( dpid id );
        //get group instances by model instance id
        unsigned int getGroupInstancesByInstance( dpid instance_id, std::list<model_group_instance_ref *> *l );
        //get group instances by model instance id and parent group id
        unsigned int getGroupInstancesByInstanceAndParent( dpid instance_id, dpid parent_id, std::list<model_group_instance_ref *> *l );
        //release list returned by getGroupInstances()
        void releaseGetGroupInstances( std::list<model_group_instance_ref *> *l );
        //find triangle instance
        model_triangle_instance_ref *findTriangleInstance( dpid id );
        //get group instances by model instance id
        unsigned int getTriangleInstancesByInstance( dpid instance_id, std::list<model_triangle_instance_ref *> *l );
        //get triangle instances by model instance id and parent group id
        unsigned int getTriangleInstancesByInstanceAndGroup( dpid instance_id, dpid group_id, std::list<model_triangle_instance_ref *> *l );
        //release list returned by getTriangleInstances()
        void releaseGetTriangleInstances( std::list<model_triangle_instance_ref *> *l );
        //find triangle vertex instance
        model_triangle_vertex_instance_ref *findTriangleVertexInstance( dpid id );
        //get triangle vertex instances by model instance id
        unsigned int getTriangleVertexInstancesByInstance( dpid instance_id, std::list<model_triangle_vertex_instance_ref *> *l );
        //get triangle vertex instances by model instance id and parent triangle id
        unsigned int getTriangleVertexInstancesByInstanceAndTriangle( dpid instance_id, dpid triangle_id, std::list<model_triangle_vertex_instance_ref *> *l );
        //release list returned by getTriangleVertexInstances()
        void releaseGetTriangleVertexInstances( std::list<model_triangle_vertex_instance_ref *> *l );
        //find vertex instance
        model_vertex_instance_ref *findVertexInstance( dpid id );
        //get  vertex instances by model instance id
        unsigned int getVertexInstancesByInstance( dpid instance_id, std::list<model_vertex_instance_ref *> *l );
        //release list returned by getVertexInstances()
        void releaseGetVertexInstances( std::list<model_vertex_instance_ref *> *l );

        friend class model;
    };
    
};

#endif