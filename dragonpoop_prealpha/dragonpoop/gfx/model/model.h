
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

    class model : public shared_obj
    {

    private:

        core *c;
        gfx_ref *g;
        std::string sname;
        dpid id, default_anim_id;
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
        //add new comp
        void addComp( model_component *c, dpid id, uint16_t ctype, dpid parent_0, dpid parent_1, dpid parent_2 );
        //add new comp
        void addComp( model_component *c, dpid id, uint16_t ctype, dpid parent_0, dpid parent_1, dpid parent_2, dpid parent_3 );
        //clear all components from model
        void clear( void );
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
        //get components by two owners
        unsigned int getComponentsByTwoOwners( std::list<model_component_ref *> *l, dpid id0, dpid id1 );
        //get componetns by two owners and type
        unsigned int getComponentsByTwoOwnersAndType( std::list<model_component_ref *> *l, dpid id0, dpid id1, uint16_t ctype );
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
        //create a material
        model_material_ref *createMaterial( dpthread_lock *thd, model_writelock *m );
        //find a material by id
        model_material_ref *findMaterial( dpid id );
        //get all materials
        unsigned int getMaterials( std::list<model_material_ref *> *l );
        //release list returned by getMateriales()
        static void releaseGetMaterials( std::list<model_material_ref *> *l );
        //create a animation
        model_animation_ref *createAnimation( dpthread_lock *thd, model_writelock *m );
        //find a animation by id
        model_animation_ref *findAnimation( dpid id );
        //get all animations
        unsigned int getAnimations( std::list<model_animation_ref *> *l );
        //release list returned by getAnimations()
        static void releaseGetAnimations( std::list<model_animation_ref *> *l );
        //create a Frame
        model_frame_ref *createFrame( dpthread_lock *thd, model_writelock *m );
        //find a Frame by id
        model_frame_ref *findFrame( dpid id );
        //get all Frames
        unsigned int getFrames( std::list<model_frame_ref *> *l );
        //release list returned by getFrames()
        static void releaseGetFrames( std::list<model_frame_ref *> *l );
        //create a animation_frame
        model_animation_frame_ref *createAnimationFrame( dpthread_lock *thd, model_writelock *m, dpid animation_id, dpid frame_id, float ftime );
        //find a animation_frame by id
        model_animation_frame_ref *findAnimationFrame( dpid id );
        //get all animation_frames
        unsigned int getAnimationFrames( std::list<model_animation_frame_ref *> *l );
        //get all animation_frames by animation id
        unsigned int getAnimationFramesByAnimation( std::list<model_animation_frame_ref *> *l, dpid anim_id );
        //release list returned by getAnimationFrames()
        static void releaseGetAnimationFrames( std::list<model_animation_frame_ref *> *l );
        //create a frame joint
        model_frame_joint_ref *createFrameJoint( dpthread_lock *thd, model_writelock *m, dpid frame_id, dpid joint_id );
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
        static void releaseGetFrameJoints( std::list<model_frame_joint_ref *> *l );
        //create a joint
        model_joint_ref *createJoint( dpthread_lock *thd, model_writelock *m );
        //create a joint
        model_joint_ref *createJoint( dpthread_lock *thd, model_writelock *m, dpid parent_id );
        //find a joint by id
        model_joint_ref *findJoint( dpid id );
        //get all joints
        unsigned int getJoints( std::list<model_joint_ref *> *l );
        //get all joints by parent id
        unsigned int getJointsByParent( std::list<model_joint_ref *> *l, dpid parent_id );
        //release list returned by getFrameJoints()
        static void releaseGetJoints( std::list<model_joint_ref *> *l );
        //create a vertex joint
        model_vertex_joint_ref *createVertexJoint( dpthread_lock *thd, model_writelock *m, dpid vertex_id, dpid joint_id );
        //find a vertex joint by id
        model_vertex_joint_ref *findVertexJoint( dpid id );
        //get all vertex joints
        unsigned int getVertexJoints( std::list<model_vertex_joint_ref *> *l );
        //get all vertex joints by vertex
        unsigned int getVertexJointsByVertex( std::list<model_vertex_joint_ref *> *l, dpid vertex_id );
        //get all vertex joints by joint
        unsigned int getVertexJointsByJoint( std::list<model_vertex_joint_ref *> *l, dpid joint_id );
        //release list returned by getVertexJoints()
        static void releaseGetVertexJoints( std::list<model_vertex_joint_ref *> *l );
        //returns default animation id
        dpid getDefaultAnimationId( void );
        //returns default animation
        model_animation_ref *getDefaultAnimation( void );
        //set default animation id
        void setDefaultAnimationId( dpid id );
        //create model instance
        model_instance_ref *createInstance( dpthread_lock *thd, model_writelock *m );
        //find model instance
        model_instance_ref *findInstance( dpid id );
        //get model instances
        unsigned int getInstances( std::list<model_instance_ref *> *l );
        //release list returned by getInstances()
        static void releaseGetInstances( std::list<model_instance_ref *> *l );
        //create group instance
        model_group_instance_ref *createGroupInstance( dpthread_lock *thd, model_writelock *m, dpid instance_id, dpid group_id, dpid parent_id, dpid material_id );
        //find group instance
        model_group_instance_ref *findGroupInstance( dpid id );
        //get group instances by model instance id
        unsigned int getGroupInstancesByInstance( dpid instance_id, std::list<model_group_instance_ref *> *l );
        //get group instances by model instance id and parent group id
        unsigned int getGroupInstancesByInstanceAndParent( dpid instance_id, dpid parent_id, std::list<model_group_instance_ref *> *l );

        //create triangle instance
        model_triangle_instance_ref *createTriangleInstance( dpthread_lock *thd, model_writelock *m, dpid instance_id, dpid triangle_id, dpid group_id );
        //find triangle instance
        model_triangle_instance_ref *findTriangleInstance( dpid id );
        //get triangle instances by model instance id
        unsigned int getTriangleInstancesByInstance( dpid instance_id, std::list<model_triangle_instance_ref *> *l );
        //get triangle instances by model instance id and parent group id
        unsigned int getTriangleInstancesByInstanceAndGroup( dpid instance_id, dpid group_id, std::list<model_triangle_instance_ref *> *l );

    public:

        //ctor
        model( gfx_writelock *g, dpid id, const char *cname );
        //dtor
        virtual ~model( void );
        //return core
        core *getCore( void );
        //returns true if alive
        bool isAlive( void );

        //release list returned by getGroupInstances()
        static void releaseGetGroupInstances( std::list<model_group_instance_ref *> *l );
        //release list returned by getTriangleInstances()
        static void releaseGetTriangleInstances( std::list<model_triangle_instance_ref *> *l );

        friend class model_readlock;
        friend class model_writelock;
    };
    
};

#endif