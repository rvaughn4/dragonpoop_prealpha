
#ifndef dragonpoop_model_writelock_h
#define dragonpoop_model_writelock_h

#include "../../core/shared_obj/shared_obj_writelock.h"
#include "../../core/dpid/dpid.h"
#include <string>
#include <list>

namespace dragonpoop
{
    class model;
    class core;
    class dpthread_lock;
    class gfx_writelock;
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
    class model_animation_instance_ref;
    class model_joint_instance_ref;

    class model_writelock : public shared_obj_writelock
    {

    private:

        model *t;

    protected:

        //ctor
        model_writelock( model *t, dpmutex_writelock *l );
        //dtor
        virtual ~model_writelock( void );

    public:

        //return core
        core *getCore( void );
        //get name
        void getName( std::string *s );
        //set name
        void setName( std::string *s );
        //set name
        void setName( const char *c );
        //set id
        void setId( dpid id );
        //get id
        dpid getId( void );
        //kill model
        void kill( void );
        //returns true if alive
        bool isAlive( void );
        //run model
        void run( dpthread_lock *thd, gfx_writelock *g );
        //clear all components from model
        void clear( void );
        //create a vertex
        model_vertex_ref *createVertex( dpthread_lock *thd );
        //get all vertexes
        unsigned int getVertexes( std::list<model_vertex_ref *> *l );
        //release list returned by getVertexes()
        void releaseGetVertexes( std::list<model_vertex_ref *> *l );
        //find a vertex by id
        model_vertex_ref *findVertex( dpid id );
        //create a group
        model_group_ref *createGroup( dpthread_lock *thd );
        //create a group
        model_group_ref *createGroup( dpthread_lock *thd, dpid parent_id );
        //find a group by id
        model_group_ref *findGroup( dpid id );
        //get all groups
        unsigned int getGroups( std::list<model_group_ref *> *l );
        //get all groups by parent
        unsigned int getGroupsByParent( std::list<model_group_ref *> *l, dpid parent_id );
        //release list returned by getGroups()
        void releaseGetGroups( std::list<model_group_ref *> *l );
        //create a triangle
        model_triangle_ref *createTriangle( dpthread_lock *thd, dpid group_id );
        //find a triangle by id
        model_triangle_ref *findTriangle( dpid id );
        //get all triangles
        unsigned int getTriangles( std::list<model_triangle_ref *> *l );
        //get all triangles belonging to group
        unsigned int getTrianglesByGroup( std::list<model_triangle_ref *> *l, dpid group_id );
        //release list returned by getTriangles()
        void releaseGetTriangles( std::list<model_triangle_ref *> *l );
        //create a triangle vertex
        model_triangle_vertex_ref *createTriangleVertex( dpthread_lock *thd, dpid triangle_id, dpid vertex_id );
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
        //create a material
        model_material_ref *createMaterial( dpthread_lock *thd );
        //find a material by id
        model_material_ref *findMaterial( dpid id );
        //get all materials
        unsigned int getMaterials( std::list<model_material_ref *> *l );
        //release list returned by getMateriales()
        void releaseGetMaterials( std::list<model_material_ref *> *l );
        //create a animation
        model_animation_ref *createAnimation( dpthread_lock *thd );
        //find a animation by id
        model_animation_ref *findAnimation( dpid id );
        //get all animations
        unsigned int getAnimations( std::list<model_animation_ref *> *l );
        //release list returned by getAnimations()
        void releaseGetAnimations( std::list<model_animation_ref *> *l );
        //create a Frame
        model_frame_ref *createFrame( dpthread_lock *thd );
        //find a Frame by id
        model_frame_ref *findFrame( dpid id );
        //get all Frames
        unsigned int getFrames( std::list<model_frame_ref *> *l );
        //release list returned by getFrames()
        static void releaseGetFrames( std::list<model_frame_ref *> *l );
        //create a animation_frame
        model_animation_frame_ref *createAnimationFrame( dpthread_lock *thd, dpid animation_id, dpid frame_id, float ftime );
        //find a animation_frame by id
        model_animation_frame_ref *findAnimationFrame( dpid id );
        //get all animation_frames
        unsigned int getAnimationFrames( std::list<model_animation_frame_ref *> *l );
        //get all animation_frames by animation id
        unsigned int getAnimationFramesByAnimation( std::list<model_animation_frame_ref *> *l, dpid anim_id );
        //release list returned by getAnimationFrames()
        void releaseGetAnimationFrames( std::list<model_animation_frame_ref *> *l );
        //create a frame joint
        model_frame_joint_ref *createFrameJoint( dpthread_lock *thd, dpid frame_id, dpid joint_id );
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
        //create a joint
        model_joint_ref *createJoint( dpthread_lock *thd );
        //create a joint
        model_joint_ref *createJoint( dpthread_lock *thd, dpid parent_id );
        //find a joint by id
        model_joint_ref *findJoint( dpid id );
        //get all joints
        unsigned int getJoints( std::list<model_joint_ref *> *l );
        //get all joints by parent id
        unsigned int getJointsByParent( std::list<model_joint_ref *> *l, dpid parent_id );
        //release list returned by getFrameJoints()
        void releaseGetJoints( std::list<model_joint_ref *> *l );
        //create a vertex joint
        model_vertex_joint_ref *createVertexJoint( dpthread_lock *thd, dpid vertex_id, dpid joint_id );
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
        //create model instance
        model_instance_ref *createInstance( dpthread_lock *thd );
        //find model instance
        model_instance_ref *findInstance( dpid id );
        //get model instances
        unsigned int getInstances( std::list<model_instance_ref *> *l );
        //release list returned by getInstances()
        void releaseGetInstances( std::list<model_instance_ref *> *l );
        //create group instance
        model_group_instance_ref *createGroupInstance( dpthread_lock *thd, dpid instance_id, dpid group_id, dpid parent_id, dpid material_id );
        //find group instance
        model_group_instance_ref *findGroupInstance( dpid id );
        //get group instances by model instance id
        unsigned int getGroupInstancesByInstance( dpid instance_id, std::list<model_group_instance_ref *> *l );
        //get group instances by model instance id and parent group id
        unsigned int getGroupInstancesByInstanceAndParent( dpid instance_id, dpid parent_id, std::list<model_group_instance_ref *> *l );
        //release list returned by getGroupInstances()
        void releaseGetGroupInstances( std::list<model_group_instance_ref *> *l );
        //create triangle instance
        model_triangle_instance_ref *createTriangleInstance( dpthread_lock *thd, dpid instance_id, dpid triangle_id, dpid group_id );
        //find triangle instance
        model_triangle_instance_ref *findTriangleInstance( dpid id );
        //get group instances by model instance id
        unsigned int getTriangleInstancesByInstance( dpid instance_id, std::list<model_triangle_instance_ref *> *l );
        //get triangle instances by model instance id and parent group id
        unsigned int getTriangleInstancesByInstanceAndGroup( dpid instance_id, dpid group_id, std::list<model_triangle_instance_ref *> *l );
        //release list returned by getTriangleInstances()
        void releaseGetTriangleInstances( std::list<model_triangle_instance_ref *> *l );
        //create animation instance
        model_animation_instance_ref *createAnimationInstance( dpthread_lock *thd, dpid instance_id, dpid animation_id );
        //find animation instance
        model_animation_instance_ref *findAnimationInstance( dpid id );
        //get animation instances by model instance id
        unsigned int getAnimationInstancesByInstance( dpid instance_id, std::list<model_animation_instance_ref *> *l );
        //release list returned by getAnimationInstances()
        void releaseGetAnimationInstances( std::list<model_animation_instance_ref *> *l );
        //create joint instance
        model_joint_instance_ref *createJointInstance( dpthread_lock *thd, dpid instance_id, dpid joint_id );
        //find joint instance
        model_joint_instance_ref *findJointInstance( dpid id );
        //get joint instances by model instance id
        unsigned int getJointInstancesByInstance( dpid instance_id, std::list<model_animation_instance_ref *> *l );
        //release list returned by getJointInstances()
        void releaseGetJointInstances( std::list<model_joint_instance_ref *> *l );

        friend class model;
    };
    
};

#endif