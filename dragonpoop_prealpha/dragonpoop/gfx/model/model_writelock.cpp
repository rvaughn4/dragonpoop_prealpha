
#include "model_writelock.h"
#include "model.h"

namespace dragonpoop
{

    //ctor
    model_writelock::model_writelock( model *t, dpmutex_writelock *l ) : shared_obj_writelock( t, l )
    {
        this->t = t;
    }

    //dtor
    model_writelock::~model_writelock( void )
    {

    }

    //return core
    core *model_writelock::getCore( void )
    {
        return this->t->getCore();
    }

    //get name
    void model_writelock::getName( std::string *s )
    {
        this->t->getName( s );
    }

    //get name
    void model_writelock::setName( const char *c )
    {
        this->t->setName( c );
    }

    //get name
    void model_writelock::setName( std::string *s )
    {
        this->t->setName( s );
    }

    //set id
    void model_writelock::setId( dpid id )
    {
        this->t->setId( id );
    }

    //get id
    dpid model_writelock::getId( void )
    {
        return this->t->getId();
    }

    //kill model
    void model_writelock::kill( void )
    {
        this->t->kill();
    }

    //returns true if alive
    bool model_writelock::isAlive( void )
    {
        return this->t->isAlive();
    }

    //run model
    void model_writelock::run( dpthread_lock *thd, gfx_writelock *g )
    {
        this->t->run( thd, g, this );
    }

    //create a vertex
    model_vertex_ref *model_writelock::createVertex( dpthread_lock *thd )
    {
        return this->t->createVertex( thd, this );
    }

    //get all vertexes
    unsigned int model_writelock::getVertexes( std::list<model_vertex_ref *> *l )
    {
        return this->t->getVertexes( l );
    }

    //release list returned by getVertexes()
    void model_writelock::releaseGetVertexes( std::list<model_vertex_ref *> *l )
    {
        model::releaseGetVertexes( l );
    }

    //find a vertex by id
    model_vertex_ref *model_writelock::findVertex( dpid id )
    {
        return this->t->findVertex( id );
    }

    //create a group
    model_group_ref *model_writelock::createGroup( dpthread_lock *thd )
    {
        return this->t->createGroup( thd, this );
    }

    //create a group
    model_group_ref *model_writelock::createGroup( dpthread_lock *thd, dpid parent_id )
    {
        return this->t->createGroup( thd, this, parent_id );
    }

    //find a group by id
    model_group_ref *model_writelock::findGroup( dpid id )
    {
        return this->t->findGroup( id );
    }

    //get all groups
    unsigned int model_writelock::getGroups( std::list<model_group_ref *> *l )
    {
        return this->t->getGroups( l );
    }

    //get all groups
    unsigned int model_writelock::getGroupsByParent( std::list<model_group_ref *> *l, dpid parent_id )
    {
        return this->t->getGroupsByParent( l, parent_id );
    }

    //release list returned by getGroups()
    void model_writelock::releaseGetGroups( std::list<model_group_ref *> *l )
    {
        model::releaseGetGroups( l );
    }

    //create a triangle
    model_triangle_ref *model_writelock::createTriangle( dpthread_lock *thd, dpid group_id )
    {
        return this->t->createTriangle( thd, this, group_id );
    }

    //find a triangle by id
    model_triangle_ref *model_writelock::findTriangle( dpid id )
    {
        return this->t->findTriangle( id );
    }

    //get all triangles
    unsigned int model_writelock::getTriangles( std::list<model_triangle_ref *> *l )
    {
        return this->t->getTriangles( l );
    }

    //get all triangles belonging to group
    unsigned int model_writelock::getTrianglesByGroup( std::list<model_triangle_ref *> *l, dpid group_id )
    {
        return this->t->getTrianglesByGroup( l, group_id );
    }

    //release list returned by getTriangles()
    void model_writelock::releaseGetTriangles( std::list<model_triangle_ref *> *l )
    {
        model::releaseGetTriangles( l );
    }

    //create a triangle vertex
    model_triangle_vertex_ref *model_writelock::createTriangleVertex( dpthread_lock *thd, dpid triangle_id, dpid vertex_id )
    {
        return this->t->createTriangleVertex( thd, this, triangle_id, vertex_id );
    }

    //find a triangle vertex by id
    model_triangle_vertex_ref *model_writelock::findTriangleVertex( dpid id )
    {
        return this->t->findTriangleVertex( id );
    }

    //get all triangle vertexes
    unsigned int model_writelock::getTriangleVertexes( std::list<model_triangle_vertex_ref *> *l )
    {
        return this->t->getTriangleVertexes( l );
    }

    //get all triangle vertexes belonging to triangle
    unsigned int model_writelock::getTriangleVertexesByTriangle( std::list<model_triangle_vertex_ref *> *l, dpid triangle_id )
    {
        return this->t->getTriangleVertexesByTriangle( l, triangle_id );
    }

    //get all triangle vertexes belonging to vertex
    unsigned int model_writelock::getTriangleVertexesByVertex( std::list<model_triangle_vertex_ref *> *l, dpid vertex_id )
    {
        return this->t->getTriangleVertexesByVertex( l, vertex_id );
    }

    //release list returned by getTriangleVertexes()
    void model_writelock::releaseGetTriangleVertexes( std::list<model_triangle_vertex_ref *> *l )
    {
        model::releaseGetTriangleVertexes( l );
    }

    //clear all components from model
    void model_writelock::clear( void )
    {
        this->t->clear();
    }

    //create a material
    model_material_ref *model_writelock::createMaterial( dpthread_lock *thd )
    {
        return this->t->createMaterial( thd, this );
    }

    //find a material by id
    model_material_ref *model_writelock::findMaterial( dpid id )
    {
        return this->t->findMaterial( id );
    }

    //get all materials
    unsigned int model_writelock::getMaterials( std::list<model_material_ref *> *l )
    {
        return this->t->getMaterials( l );
    }

    //release list returned by getMateriales()
    void model_writelock::releaseGetMaterials( std::list<model_material_ref *> *l )
    {
        model::releaseGetMaterials( l );
    }

    //create a animation
    model_animation_ref *model_writelock::createAnimation( dpthread_lock *thd )
    {
        return this->t->createAnimation( thd, this );
    }

    //find a animation by id
    model_animation_ref *model_writelock::findAnimation( dpid id )
    {
        return this->t->findAnimation( id );
    }

    //get all animations
    unsigned int model_writelock::getAnimations( std::list<model_animation_ref *> *l )
    {
        return this->t->getAnimations( l );
    }

    //release list returned by getanimationes()
    void model_writelock::releaseGetAnimations( std::list<model_animation_ref *> *l )
    {
        model::releaseGetAnimations( l );
    }

    //create a frame
    model_frame_ref *model_writelock::createFrame( dpthread_lock *thd )
    {
        return this->t->createFrame( thd, this );
    }

    //find a frame by id
    model_frame_ref *model_writelock::findFrame( dpid id )
    {
        return this->t->findFrame( id );
    }

    //get all frames
    unsigned int model_writelock::getFrames( std::list<model_frame_ref *> *l )
    {
        return this->t->getFrames( l );
    }

    //release list returned by getframees()
    void model_writelock::releaseGetFrames( std::list<model_frame_ref *> *l )
    {
        model::releaseGetFrames( l );
    }

    //create a animation_frame
    model_animation_frame_ref *model_writelock::createAnimationFrame( dpthread_lock *thd, dpid animation_id, dpid frame_id, float ftime )
    {
        return this->t->createAnimationFrame( thd, this, animation_id, frame_id, ftime );
    }

    //find a animation_frame by id
    model_animation_frame_ref *model_writelock::findAnimationFrame( dpid id )
    {
        return this->t->findAnimationFrame( id );
    }

    //get all animation_frames
    unsigned int model_writelock::getAnimationFrames( std::list<model_animation_frame_ref *> *l )
    {
        return this->t->getAnimationFrames( l );
    }

    //get all animation_frames by animation id
    unsigned int model_writelock::getAnimationFramesByAnimation( std::list<model_animation_frame_ref *> *l, dpid anim_id )
    {
        return this->t->getAnimationFramesByAnimation( l, anim_id );
    }

    //release list returned by getanimation_framees()
    void model_writelock::releaseGetAnimationFrames( std::list<model_animation_frame_ref *> *l )
    {
        model::releaseGetAnimationFrames( l );
    }

    //create a frame joint
    model_frame_joint_ref *model_writelock::createFrameJoint( dpthread_lock *thd, dpid frame_id, dpid joint_id )
    {
        return this->t->createFrameJoint( thd, this, frame_id, joint_id );
    }

    //find a frame joint by id
    model_frame_joint_ref *model_writelock::findFrameJoint( dpid id )
    {
        return this->t->findFrameJoint( id );
    }

    //get all frame joints
    unsigned int model_writelock::getFrameJoints( std::list<model_frame_joint_ref *> *l )
    {
        return this->t->getFrameJoints( l );
    }

    //get all frame joints by frame id
    unsigned int model_writelock::getFrameJointsByFrame( std::list<model_frame_joint_ref *> *l, dpid frame_id )
    {
        return this->t->getFrameJointsByFrame( l, frame_id );
    }

    //get all frame joints by joint id
    unsigned int model_writelock::getFrameJointsByJoint( std::list<model_frame_joint_ref *> *l, dpid joint_id )
    {
        return this->t->getFrameJointsByJoint( l, joint_id );
    }

    //get all frame joints by joint and frame id
    unsigned int model_writelock::getFrameJointsByFrameAndJoint( std::list<model_frame_joint_ref *> *l, dpid frame_id, dpid joint_id )
    {
        return this->t->getFrameJointsByFrameAndJoint( l, frame_id, joint_id );
    }

    //release list returned by getFrameJoints()
    void model_writelock::releaseGetFrameJoints( std::list<model_frame_joint_ref *> *l )
    {
        model::releaseGetFrameJoints( l );
    }

    //create a joint
    model_joint_ref *model_writelock::createJoint( dpthread_lock *thd )
    {
        return this->t->createJoint( thd, this );
    }

    //create a joint
    model_joint_ref *model_writelock::createJoint( dpthread_lock *thd, dpid parent_id )
    {
        return this->t->createJoint( thd, this, parent_id );
    }

    //find a joint by id
    model_joint_ref *model_writelock::findJoint( dpid id )
    {
        return this->t->findJoint( id );
    }

    //get all joints
    unsigned int model_writelock::getJoints( std::list<model_joint_ref *> *l )
    {
        return this->t->getJoints( l );
    }

    //get all joints by parent id
    unsigned int model_writelock::getJointsByParent( std::list<model_joint_ref *> *l, dpid parent_id )
    {
        return this->t->getJointsByParent( l, parent_id );
    }

    //release list returned by getJoints()
    void model_writelock::releaseGetJoints( std::list<model_joint_ref *> *l )
    {
        model::releaseGetJoints( l );
    }

    //create a vertex joint
    model_vertex_joint_ref *model_writelock::createVertexJoint( dpthread_lock *thd, dpid vertex_id, dpid joint_id )
    {
        return this->t->createVertexJoint( thd, this, vertex_id, joint_id );
    }

    //find a vertex joint by id
    model_vertex_joint_ref *model_writelock::findVertexJoint( dpid id )
    {
        return this->t->findVertexJoint( id );
    }

    //get all vertex joints
    unsigned int model_writelock::getVertexJoints( std::list<model_vertex_joint_ref *> *l )
    {
        return this->t->getVertexJoints( l );
    }

    //get all vertex joints by vertex
    unsigned int model_writelock::getVertexJointsByVertex( std::list<model_vertex_joint_ref *> *l, dpid vertex_id )
    {
        return this->t->getVertexJointsByVertex( l, vertex_id );
    }

    //get all vertex joints
    unsigned int model_writelock::getVertexJointsByJoint( std::list<model_vertex_joint_ref *> *l, dpid joint_id )
    {
        return this->t->getVertexJointsByJoint( l, joint_id );
    }

    //release list returned by getVertexJoints()
    void model_writelock::releaseGetVertexJoints( std::list<model_vertex_joint_ref *> *l )
    {
        model::releaseGetVertexJoints( l );
    }

    //returns default animation id
    dpid model_writelock::getDefaultAnimationId( void )
    {
        return this->t->getDefaultAnimationId();
    }

    //returns default animation
    model_animation_ref *model_writelock::getDefaultAnimation( void )
    {
        return this->t->getDefaultAnimation();
    }

    //set default animation id
    void model_writelock::setDefaultAnimationId( dpid id )
    {
        this->t->setDefaultAnimationId( id );
    }

    //create model instance
    model_instance_ref *model_writelock::createInstance( dpthread_lock *thd )
    {
        return this->t->createInstance( thd, this );
    }

    //find model instance
    model_instance_ref *model_writelock::findInstance( dpid id )
    {
        return this->t->findInstance( id );
    }

    //get model instances
    unsigned int model_writelock::getInstances( std::list<model_instance_ref *> *l )
    {
        return this->t->getInstances( l );
    }

    //release list returned by getInstances()
    void model_writelock::releaseGetInstances( std::list<model_instance_ref *> *l )
    {
        model::releaseGetInstances( l );
    }

    //create group instance
    model_group_instance_ref *model_writelock::createGroupInstance( dpthread_lock *thd, dpid instance_id, dpid group_id, dpid parent_id, dpid material_id )
    {
        return this->t->createGroupInstance( thd, this, instance_id, group_id, parent_id, material_id );
    }

    //find group instance
    model_group_instance_ref *model_writelock::findGroupInstance( dpid id )
    {
        return this->t->findGroupInstance( id );
    }

    //get group instances by model instance id
    unsigned int model_writelock::getGroupInstancesByInstance( dpid instance_id, std::list<model_group_instance_ref *> *l )
    {
        return this->t->getGroupInstancesByInstance( instance_id, l );
    }

    //get group instances by model instance id and parent group id
    unsigned int model_writelock::getGroupInstancesByInstanceAndParent( dpid instance_id, dpid parent_id, std::list<model_group_instance_ref *> *l )
    {
        return this->t->getGroupInstancesByInstanceAndParent( instance_id, parent_id, l );
    }

    //release list returned by getGroupInstances()
    void model_writelock::releaseGetGroupInstances( std::list<model_group_instance_ref *> *l )
    {
        model::releaseGetGroupInstances( l );
    }

    //create triangle instance
    model_triangle_instance_ref *model_writelock::createTriangleInstance( dpthread_lock *thd, dpid instance_id, dpid triangle_id, dpid group_id )
    {
        return this->t->createTriangleInstance( thd, this, instance_id, triangle_id, group_id );
    }

    //find triangle instance
    model_triangle_instance_ref *model_writelock::findTriangleInstance( dpid id )
    {
        return this->t->findTriangleInstance( id );
    }

    //get group instances by model instance id
    unsigned int model_writelock::getTriangleInstancesByInstance( dpid instance_id, std::list<model_triangle_instance_ref *> *l )
    {
        return this->t->getTriangleInstancesByInstance( instance_id, l );
    }

    //get triangle instances by model instance id and parent group id
    unsigned int model_writelock::getTriangleInstancesByInstanceAndGroup( dpid instance_id, dpid group_id, std::list<model_triangle_instance_ref *> *l )
    {
        return this->t->getTriangleInstancesByInstanceAndGroup( instance_id, group_id, l );
    }

    //release list returned by getTriangleInstances()
    void model_writelock::releaseGetTriangleInstances( std::list<model_triangle_instance_ref *> *l )
    {
        model::releaseGetTriangleInstances( l );
    }

    //create animation instance
    model_animation_instance_ref *model_writelock::createAnimationInstance( dpthread_lock *thd, dpid instance_id, dpid animation_id )
    {
        return this->t->createAnimationInstance( thd, this, instance_id, animation_id );
    }

    //find animation instance
    model_animation_instance_ref *model_writelock::findAnimationInstance( dpid id )
    {
        return this->t->findAnimationInstance( id );
    }

    //get animation instances by model instance id
    unsigned int model_writelock::getAnimationInstancesByInstance( dpid instance_id, std::list<model_animation_instance_ref *> *l )
    {
        return this->t->getAnimationInstancesByInstance( instance_id, l );
    }

    //release list returned by getAnimationInstances()
    void model_writelock::releaseGetAnimationInstances( std::list<model_animation_instance_ref *> *l )
    {
        model::releaseGetAnimationInstances( l );
    }

};
