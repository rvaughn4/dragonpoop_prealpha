
#include "model_readlock.h"
#include "model.h"

namespace dragonpoop
{

    //ctor
    model_readlock::model_readlock( model *t, dpmutex_readlock *l ) : shared_obj_readlock( t, l )
    {
        this->t = t;
    }

    //dtor
    model_readlock::~model_readlock( void )
    {

    }

    //return core
    core *model_readlock::getCore( void )
    {
        return this->t->getCore();
    }

    //get name
    void model_readlock::getName( std::string *s )
    {
        this->t->getName( s );
    }

    //get id
    dpid model_readlock::getId( void )
    {
        return this->t->getId();
    }

    //returns true if alive
    bool model_readlock::isAlive( void )
    {
        return this->t->isAlive();
    }

    //get all vertexes
    unsigned int model_readlock::getVertexes( std::list<model_vertex_ref *> *l )
    {
        return this->t->getVertexes( l );
    }

    //release list returned by getVertexes()
    void model_readlock::releaseGetVertexes( std::list<model_vertex_ref *> *l )
    {
        model::releaseGetVertexes( l );
    }

    //find a vertex by id
    model_vertex_ref *model_readlock::findVertex( dpid id )
    {
        return this->t->findVertex( id );
    }

    //find a group by id
    model_group_ref *model_readlock::findGroup( dpid id )
    {
        return this->t->findGroup( id );
    }

    //get all groups
    unsigned int model_readlock::getGroups( std::list<model_group_ref *> *l )
    {
        return this->t->getGroups( l );
    }

    //get all groups
    unsigned int model_readlock::getGroupsByParent( std::list<model_group_ref *> *l, dpid parent_id )
    {
        return this->t->getGroupsByParent( l, parent_id );
    }

    //release list returned by getGroups()
    void model_readlock::releaseGetGroups( std::list<model_group_ref *> *l )
    {
        model::releaseGetGroups( l );
    }

    //find a triangle by id
    model_triangle_ref *model_readlock::findTriangle( dpid id )
    {
        return this->t->findTriangle( id );
    }

    //get all triangles
    unsigned int model_readlock::getTriangles( std::list<model_triangle_ref *> *l )
    {
        return this->t->getTriangles( l );
    }

    //get all triangles belonging to group
    unsigned int model_readlock::getTrianglesByGroup( std::list<model_triangle_ref *> *l, dpid group_id )
    {
        return this->t->getTrianglesByGroup( l, group_id );
    }

    //release list returned by getTriangles()
    void model_readlock::releaseGetTriangles( std::list<model_triangle_ref *> *l )
    {
        model::releaseGetTriangles( l );
    }

    //find a triangle vertex by id
    model_triangle_vertex_ref *model_readlock::findTriangleVertex( dpid id )
    {
        return this->t->findTriangleVertex( id );
    }

    //get all triangle vertexes
    unsigned int model_readlock::getTriangleVertexes( std::list<model_triangle_vertex_ref *> *l )
    {
        return this->t->getTriangleVertexes( l );
    }

    //get all triangle vertexes belonging to triangle
    unsigned int model_readlock::getTriangleVertexesByTriangle( std::list<model_triangle_vertex_ref *> *l, dpid triangle_id )
    {
        return this->t->getTriangleVertexesByTriangle( l, triangle_id );
    }

    //get all triangle vertexes belonging to vertex
    unsigned int model_readlock::getTriangleVertexesByVertex( std::list<model_triangle_vertex_ref *> *l, dpid vertex_id )
    {
        return this->t->getTriangleVertexesByVertex( l, vertex_id );
    }

    //release list returned by getTriangleVertexes()
    void model_readlock::releaseGetTriangleVertexes( std::list<model_triangle_vertex_ref *> *l )
    {
        model::releaseGetTriangleVertexes( l );
    }

    //find a material by id
    model_material_ref *model_readlock::findMaterial( dpid id )
    {
        return this->t->findMaterial( id );
    }

    //get all materials
    unsigned int model_readlock::getMaterials( std::list<model_material_ref *> *l )
    {
        return this->t->getMaterials( l );
    }

    //release list returned by getMateriales()
    void model_readlock::releaseGetMaterials( std::list<model_material_ref *> *l )
    {
        model::releaseGetMaterials( l );
    }

    //find a animation by id
    model_animation_ref *model_readlock::findAnimation( dpid id )
    {
        return this->t->findAnimation( id );
    }

    //get all animations
    unsigned int model_readlock::getAnimations( std::list<model_animation_ref *> *l )
    {
        return this->t->getAnimations( l );
    }

    //release list returned by getanimationes()
    void model_readlock::releaseGetAnimations( std::list<model_animation_ref *> *l )
    {
        model::releaseGetAnimations( l );
    }

    //find a frame by id
    model_frame_ref *model_readlock::findFrame( dpid id )
    {
        return this->t->findFrame( id );
    }

    //get all frames
    unsigned int model_readlock::getFrames( std::list<model_frame_ref *> *l )
    {
        return this->t->getFrames( l );
    }

    //release list returned by getframees()
    void model_readlock::releaseGetFrames( std::list<model_frame_ref *> *l )
    {
        model::releaseGetFrames( l );
    }

    //find a animation_frame by id
    model_animation_frame_ref *model_readlock::findAnimationFrame( dpid id )
    {
        return this->t->findAnimationFrame( id );
    }

    //get all animation_frames
    unsigned int model_readlock::getAnimationFrames( std::list<model_animation_frame_ref *> *l )
    {
        return this->t->getAnimationFrames( l );
    }

    //get all animation_frames by animation id
    unsigned int model_readlock::getAnimationFramesByAnimation( std::list<model_animation_frame_ref *> *l, dpid anim_id )
    {
        return this->t->getAnimationFramesByAnimation( l, anim_id );
    }

    //release list returned by getanimation_framees()
    void model_readlock::releaseGetAnimationFrames( std::list<model_animation_frame_ref *> *l )
    {
        model::releaseGetAnimationFrames( l );
    }

    //find a frame joint by id
    model_frame_joint_ref *model_readlock::findFrameJoint( dpid id )
    {
        return this->t->findFrameJoint( id );
    }

    //get all frame joints
    unsigned int model_readlock::getFrameJoints( std::list<model_frame_joint_ref *> *l )
    {
        return this->t->getFrameJoints( l );
    }

    //get all frame joints by frame id
    unsigned int model_readlock::getFrameJointsByFrame( std::list<model_frame_joint_ref *> *l, dpid frame_id )
    {
        return this->t->getFrameJointsByFrame( l, frame_id );
    }

    //get all frame joints by joint id
    unsigned int model_readlock::getFrameJointsByJoint( std::list<model_frame_joint_ref *> *l, dpid joint_id )
    {
        return this->t->getFrameJointsByJoint( l, joint_id );
    }

    //get all frame joints by joint and frame id
    unsigned int model_readlock::getFrameJointsByFrameAndJoint( std::list<model_frame_joint_ref *> *l, dpid frame_id, dpid joint_id )
    {
        return this->t->getFrameJointsByFrameAndJoint( l, frame_id, joint_id );
    }

    //release list returned by getFrameJoints()
    void model_readlock::releaseGetFrameJoints( std::list<model_frame_joint_ref *> *l )
    {
        model::releaseGetFrameJoints( l );
    }

    //find a joint by id
    model_joint_ref *model_readlock::findJoint( dpid id )
    {
        return this->t->findJoint( id );
    }

    //get all joints
    unsigned int model_readlock::getJoints( std::list<model_joint_ref *> *l )
    {
        return this->t->getJoints( l );
    }

    //get all joints by parent id
    unsigned int model_readlock::getJointsByParent( std::list<model_joint_ref *> *l, dpid parent_id )
    {
        return this->t->getJointsByParent( l, parent_id );
    }

    //release list returned by getJoints()
    void model_readlock::releaseGetJoints( std::list<model_joint_ref *> *l )
    {
        model::releaseGetJoints( l );
    }

    //find a vertex joint by id
    model_vertex_joint_ref *model_readlock::findVertexJoint( dpid id )
    {
        return this->t->findVertexJoint( id );
    }

    //get all vertex joints
    unsigned int model_readlock::getVertexJoints( std::list<model_vertex_joint_ref *> *l )
    {
        return this->t->getVertexJoints( l );
    }

    //get all vertex joints by vertex
    unsigned int model_readlock::getVertexJointsByVertex( std::list<model_vertex_joint_ref *> *l, dpid vertex_id )
    {
        return this->t->getVertexJointsByVertex( l, vertex_id );
    }

    //get all vertex joints
    unsigned int model_readlock::getVertexJointsByJoint( std::list<model_vertex_joint_ref *> *l, dpid joint_id )
    {
        return this->t->getVertexJointsByJoint( l, joint_id );
    }

    //release list returned by getVertexJoints()
    void model_readlock::releaseGetVertexJoints( std::list<model_vertex_joint_ref *> *l )
    {
        model::releaseGetVertexJoints( l );
    }

    //returns default animation id
    dpid model_readlock::getDefaultAnimationId( void )
    {
        return this->t->getDefaultAnimationId();
    }

    //returns default animation
    model_animation_ref *model_readlock::getDefaultAnimation( void )
    {
        return this->t->getDefaultAnimation();
    }

    //set default animation id
    void model_readlock::setDefaultAnimationId( dpid id )
    {
        this->t->setDefaultAnimationId( id );
    }

    //find model instance
    model_instance_ref *model_readlock::findInstance( dpid id )
    {
        return this->t->findInstance( id );
    }

    //get model instances
    unsigned int model_readlock::getInstances( std::list<model_instance_ref *> *l )
    {
        return this->t->getInstances( l );
    }

    //release list returned by getInstances()
    void model_readlock::releaseGetInstances( std::list<model_instance_ref *> *l )
    {
        model::releaseGetInstances( l );
    }

    //find group instance
    model_group_instance_ref *model_readlock::findGroupInstance( dpid id )
    {
        return this->t->findGroupInstance( id );
    }

    //get group instances by model instance id
    unsigned int model_readlock::getGroupInstancesByInstance( dpid instance_id, std::list<model_group_instance_ref *> *l )
    {
        return this->t->getGroupInstancesByInstance( instance_id, l );
    }

    //get group instances by model instance id and parent group id
    unsigned int model_readlock::getGroupInstancesByInstanceAndParent( dpid instance_id, dpid parent_id, std::list<model_group_instance_ref *> *l )
    {
        return this->t->getGroupInstancesByInstanceAndParent( instance_id, parent_id, l );
    }

    //release list returned by getGroupInstances()
    void model_readlock::releaseGetGroupInstances( std::list<model_group_instance_ref *> *l )
    {
        model::releaseGetGroupInstances( l );
    }

    //find triangle instance
    model_triangle_instance_ref *model_readlock::findTriangleInstance( dpid id )
    {
        return this->t->findTriangleInstance( id );
    }

    //get group instances by model instance id
    unsigned int model_readlock::getTriangleInstancesByInstance( dpid instance_id, std::list<model_triangle_instance_ref *> *l )
    {
        return this->t->getTriangleInstancesByInstance( instance_id, l );
    }

    //get triangle instances by model instance id and parent group id
    unsigned int model_readlock::getTriangleInstancesByInstanceAndGroup( dpid instance_id, dpid group_id, std::list<model_triangle_instance_ref *> *l )
    {
        return this->t->getTriangleInstancesByInstanceAndGroup( instance_id, group_id, l );
    }

    //release list returned by getTriangleInstances()
    void model_readlock::releaseGetTriangleInstances( std::list<model_triangle_instance_ref *> *l )
    {
        model::releaseGetTriangleInstances( l );
    }

    //find animation instance
    model_animation_instance_ref *model_readlock::findAnimationInstance( dpid id )
    {
        return this->t->findAnimationInstance( id );
    }

    //get animation instances by model instance id
    unsigned int model_readlock::getAnimationInstancesByInstance( dpid instance_id, std::list<model_animation_instance_ref *> *l )
    {
        return this->t->getAnimationInstancesByInstance( instance_id, l );
    }

    //release list returned by getAnimationInstances()
    void model_readlock::releaseGetAnimationInstances( std::list<model_animation_instance_ref *> *l )
    {
        model::releaseGetAnimationInstances( l );
    }

    //find joint instance
    model_joint_instance_ref *model_readlock::findJointInstance( dpid id )
    {
        return this->t->findJointInstance( id );
    }

    //get joint instances by model instance id
    unsigned int model_readlock::getJointInstancesByInstance( dpid instance_id, std::list<model_joint_instance_ref *> *l )
    {
        return this->t->getJointInstancesByInstance( instance_id, l );
    }

    //release list returned by getJointInstances()
    void model_readlock::releaseGetJointInstances( std::list<model_joint_instance_ref *> *l )
    {
        model::releaseGetJointInstances( l );
    }

};
