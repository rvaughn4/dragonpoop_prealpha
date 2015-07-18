
#include "model.h"
#include "model_readlock.h"
#include "model_writelock.h"
#include "model_ref.h"
#include "core.h"
#include "../gfx_writelock.h"
#include "../gfx_ref.h"
#include "../../core/shared_obj/shared_obj_guard.h"
#include "../../core/dpthread/dpthread_lock.h"
#include "model_component/model_components.h"
#include "model_vertex/model_vertexes.h"
#include "model_group/model_groups.h"
#include "model_triangle/model_triangles.h"
#include "model_triangle_vertex/model_triangle_vertexes.h"
#include "model_material/model_materials.h"
#include "model_animation/model_animations.h"
#include "model_frame/model_frames.h"
#include "model_animation_frame/model_animation_frames.h"
#include "model_frame_joint/model_frame_joints.h"
#include "model_joint/model_joints.h"
#include "model_vertex_joint/model_vertex_joints.h"
#include "model_instance/model_instances.h"
#include "model_group_instance/model_group_instances.h"
#include "model_triangle_instance/model_triangle_instances.h"
#include "model_triangle_vertex_instance/model_triangle_vertex_instances.h"
#include "model_vertex_instance/model_vertex_instances.h"

namespace dragonpoop
{

    //ctor
    model::model( gfx_writelock *g, dpid id, const char *cname ) : shared_obj( g->getCore()->getMutexMaster() )
    {
        this->c = g->getCore();
        this->g = ( gfx_ref * )g->getRef();
        this->setName( cname );
        this->bAlive = 1;
        this->comps.byid = new model_component_tree_byid();
        this->comps.bytype = new model_component_tree_bytype();
        this->comps.byidtype = new model_component_tree_byidtype();
        this->comps.byowner = new model_component_tree_byowner();
        this->comps.byownertype = new model_component_tree_byownertype();
    }

    //dtor
    model::~model( void )
    {
        this->deleteComps();
        delete this->comps.byid;
        delete this->comps.bytype;
        delete this->comps.byidtype;
        delete this->comps.byowner;
        delete this->comps.byownertype;
        delete this->g;
    }

    //return core
    core *model::getCore( void )
    {
        return this->c;
    }

    //generate read lock
    shared_obj_readlock *model::genReadLock( shared_obj *p, dpmutex_readlock *l )
    {
        return new model_readlock( (model *)p, l );
    }

    //generate write lock
    shared_obj_writelock *model::genWriteLock( shared_obj *p, dpmutex_writelock *l )
    {
        return new model_writelock( (model *)p, l );
    }

    //generate ref
    shared_obj_ref *model::genRef( shared_obj *p, std::shared_ptr<shared_obj_refkernal> *k )
    {
        return new model_ref( (model *)p, k );
    }

    //set name
    void model::setName( std::string *s )
    {
        this->sname.assign( *s );
    }

    //set name
    void model::setName( const char *c )
    {
        this->sname.assign( c );
    }

    //get name
    void model::getName( std::string *s )
    {
        s->assign( this->sname );
    }

    //set id
    void model::setId( dpid id )
    {
        this->id = id;
    }

    //get id
    dpid model::getId( void )
    {
        return this->id;
    }

    //returns true if alive
    bool model::isAlive( void )
    {
        return this->bAlive;
    }

    //kill model
    void model::kill( void )
    {
        this->bAlive = 0;
    }

    //run model
    void model::run( dpthread_lock *thd, gfx_writelock *g, model_writelock *m )
    {
        this->runComps( thd, g, m );
    }

    //run model components
    void model::runComps( dpthread_lock *thd, gfx_writelock *g, model_writelock *m )
    {
        std::list<model_component *> *l, d, lc;
        std::list<model_component *>::iterator i;
        model_component *p;
        model_component_readlock *prl;
        model_component_writelock *pwl;

        shared_obj_guard o;

        l = &this->comps.lst;
        for( i = l->begin(); i != l->end(); ++i )
        {
            p = *i;
            lc.push_back( p );
        }

        l = &lc;
        for( i = l->begin(); i != l->end(); ++i )
        {
            p = *i;

            prl = (model_component_readlock *)o.tryReadLock( p, 30 );
            if( !prl )
                continue;
            if( !prl->isAlive() )
            {
                d.push_back( p );
                continue;
            }

            pwl = (model_component_writelock *)o.tryWriteLock( p, 30 );
            if( !pwl )
                continue;
            pwl->run( thd, g, m );
        }
        o.unlock();

        l = &d;
        for( i = l->begin(); i != l->end(); ++i )
        {
            p = *i;
            this->comps.lst.remove( p );
            this->comps.byid->removeLeaf( p );
            this->comps.bytype->removeLeaf( p );
            this->comps.byidtype->removeLeaf( p );
            this->comps.byowner->removeLeaf( p );
            this->comps.byownertype->removeLeaf( p );
            delete p;
        }
        l->clear();
    }

    //delete model components
    void model::deleteComps( void )
    {
        std::list<model_component *> *l, d;
        std::list<model_component *>::iterator i;
        model_component *p;

        l = &this->comps.lst;
        for( i = l->begin(); i != l->end(); ++i )
        {
            p = *i;
            d.push_back( p );
        }
        l->clear();
        this->comps.byid->clear();
        this->comps.bytype->clear();
        this->comps.byidtype->clear();
        this->comps.byowner->clear();
        this->comps.byownertype->clear();

        l = &d;
        for( i = l->begin(); i != l->end(); ++i )
        {
            p = *i;
            delete p;
        }
        l->clear();
    }

    //add new comp
    void model::addComp( model_component *c, dpid id, uint16_t ctype )
    {
        this->comps.lst.push_back( c );
        this->comps.byid->addLeaf( id, c );
        this->comps.bytype->addLeaf( ctype, c );
        this->comps.byidtype->addLeaf( id, ctype, c );
    }

    //add new comp
    void model::addComp( model_component *c, dpid id, uint16_t ctype, dpid parent_0 )
    {
        this->addComp( c, id, ctype );
        this->comps.byowner->addLeaf( parent_0, c );
        this->comps.byownertype->addLeaf( parent_0, ctype, c );
    }

    //add new comp
    void model::addComp( model_component *c, dpid id, uint16_t ctype, dpid parent_0, dpid parent_1 )
    {
        this->addComp( c, id, ctype, parent_0 );
        this->comps.byowner->addLeaf( parent_1, c );
        this->comps.byownertype->addLeaf( parent_1, ctype, c );
    }

    //add new comp
    void model::addComp( model_component *c, dpid id, uint16_t ctype, dpid parent_0, dpid parent_1, dpid parent_2 )
    {
        this->addComp( c, id, ctype, parent_0, parent_1 );
        this->comps.byowner->addLeaf( parent_2, c );
        this->comps.byownertype->addLeaf( parent_2, ctype, c );
    }

    //add new comp
    void model::addComp( model_component *c, dpid id, uint16_t ctype, dpid parent_0, dpid parent_1, dpid parent_2, dpid parent_3 )
    {
        this->addComp( c, id, ctype, parent_0, parent_1, parent_2 );
        this->comps.byowner->addLeaf( parent_3, c );
        this->comps.byownertype->addLeaf( parent_3, ctype, c );
    }

    //find model component by id
    model_component_ref *model::find( dpid id )
    {
        model_component_writelock *wl;
        model_component *o;
        shared_obj_guard g;

        o = this->comps.byid->findLeaf( id );
        if( !o )
            return 0;
        wl = (model_component_writelock *)g.writeLock( o );
        if( !wl )
            return 0;
        return (model_component_ref *)wl->getRef();
    }

    //find model component by id and type
    model_component_ref *model::find( dpid id, uint16_t ctype )
    {
        model_component_writelock *wl;
        model_component *o;
        shared_obj_guard g;

        o = this->comps.byidtype->findLeaf( id, ctype );
        if( !o )
            return 0;
        wl = (model_component_writelock *)g.writeLock( o );
        if( !wl )
            return 0;
        return (model_component_ref *)wl->getRef();
    }

    //get components by type
    unsigned int model::getComponentsByType( std::list<model_component_ref *> *l, uint16_t ctype )
    {
        std::list<model_component *> lc;

        this->comps.bytype->findLeaves( ctype, &lc );
        model::createComponentRefs( &lc, l );

        return (unsigned int)l->size();
    }

    //get components by owner
    unsigned int model::getComponentsByOwner( std::list<model_component_ref *> *l, dpid id )
    {
        std::list<model_component *> lc;

        this->comps.byowner->findLeaves( id, &lc );
        model::createComponentRefs( &lc, l );

        return (unsigned int)l->size();
    }

    //get components by owner and type
    unsigned int model::getComponentsByOwnerAndType( std::list<model_component_ref *> *l, dpid id, uint16_t ctype )
    {
        std::list<model_component *> lc;

        this->comps.byownertype->findLeaves( id, ctype, &lc );
        model::createComponentRefs( &lc, l );

        return (unsigned int)l->size();
    }

    //get components by owner
    unsigned int model::getComponentsByTwoOwners( std::list<model_component_ref *> *l, dpid id0, dpid id1 )
    {
        std::list<model_component *> lc;

        this->comps.byowner->findLeaves( id0, id1, &lc );
        model::createComponentRefs( &lc, l );

        return (unsigned int)l->size();
    }

    //get components by owner and type
    unsigned int model::getComponentsByTwoOwnersAndType( std::list<model_component_ref *> *l, dpid id0, dpid id1, uint16_t ctype )
    {
        std::list<model_component *> lc;

        this->comps.byownertype->findLeaves( id0, id1, ctype, &lc );
        model::createComponentRefs( &lc, l );

        return (unsigned int)l->size();
    }
    
    //release list retured by getComponents()
    void model::releaseGetComponents( std::list<model_component_ref *> *l )
    {
        std::list<model_component_ref *>::iterator i;
        model_component_ref *p;

        for( i = l->begin(); i != l->end(); ++i )
        {
            p = *i;
            delete p;
        }
    }

    //create a list of comp refs from list of components
    void model::createComponentRefs( std::list<model_component *> *l, std::list<model_component_ref *> *lr )
    {
        std::list<model_component *>::iterator i;
        model_component *p;
        model_component_writelock *wl;
        shared_obj_guard g;
        model_component_ref *r;

        for( i = l->begin(); i != l->end(); ++i )
        {
            p = *i;
            wl = (model_component_writelock *)g.writeLock( p );
            if( !wl )
                continue;
            r = (model_component_ref *)wl->getRef();
            if( !r )
                continue;
            lr->push_back( r );
        }
    }

    //create a vertex
    model_vertex_ref *model::createVertex( dpthread_lock *thd, model_writelock *m )
    {
        model_vertex *o;
        dpid id;
        shared_obj_guard g;
        model_vertex_writelock *ol;

        id = thd->genId();
        o = new model_vertex( m, id );
        this->addComp( o, id, model_component_type_vertex );

        ol = (model_vertex_writelock *)g.writeLock( o );
        if( !ol )
            return 0;
        return (model_vertex_ref *)ol->getRef();
    }

    //find a vertex by id
    model_vertex_ref *model::findVertex( dpid id )
    {
        return (model_vertex_ref *)this->find( id, model_component_type_vertex );
    }

    //get all vertexes
    unsigned int model::getVertexes( std::list<model_vertex_ref *> *l )
    {
        return this->getComponentsByType( (std::list<model_component_ref *> *)l, model_component_type_vertex );
    }

    //release list returned by getVertexes()
    void model::releaseGetVertexes( std::list<model_vertex_ref *> *l )
    {
        model::releaseGetComponents( (std::list<model_component_ref *> *)l );
    }

    //create a group
    model_group_ref *model::createGroup( dpthread_lock *thd, model_writelock *m )
    {
        dpid pid;
        dpid_zero( &pid );
        return this->createGroup( thd, m, pid );
    }

    //create a group
    model_group_ref *model::createGroup( dpthread_lock *thd, model_writelock *m, dpid parent_id )
    {
        model_group *o;
        dpid id;
        shared_obj_guard g;
        model_group_writelock *ol;

        id = thd->genId();
        o = new model_group( m, id, parent_id );
        this->addComp( o, id, model_component_type_group, parent_id );

        ol = (model_group_writelock *)g.writeLock( o );
        if( !ol )
            return 0;
        return (model_group_ref *)ol->getRef();
    }

    //find a group by id
    model_group_ref *model::findGroup( dpid id )
    {
        return (model_group_ref *)this->find( id, model_component_type_group );
    }

    //get all groups
    unsigned int model::getGroups( std::list<model_group_ref *> *l )
    {
        return this->getComponentsByType( (std::list<model_component_ref *> *)l, model_component_type_group );
    }

    //get all groups belonging to parent
    unsigned int model::getGroupsByParent( std::list<model_group_ref *> *l, dpid parent_id )
    {
        return this->getComponentsByOwnerAndType( (std::list<model_component_ref *> *)l, parent_id, model_component_type_group );
    }

    //release list returned by getGroups()
    void model::releaseGetGroups( std::list<model_group_ref *> *l )
    {
        model::releaseGetComponents( (std::list<model_component_ref *> *)l );
    }

    //create a triangle
    model_triangle_ref *model::createTriangle( dpthread_lock *thd, model_writelock *m, dpid group_id )
    {
        model_triangle *o;
        dpid id;
        shared_obj_guard g;
        model_triangle_writelock *ol;

        id = thd->genId();
        o = new model_triangle( m, id, group_id );
        this->addComp( o, id, model_component_type_triangle, group_id );

        ol = (model_triangle_writelock *)g.writeLock( o );
        if( !ol )
            return 0;
        return (model_triangle_ref *)ol->getRef();
    }

    //find a triangle by id
    model_triangle_ref *model::findTriangle( dpid id )
    {
        return (model_triangle_ref *)this->find( id, model_component_type_triangle );
    }

    //get all triangles
    unsigned int model::getTriangles( std::list<model_triangle_ref *> *l )
    {
        return this->getComponentsByType( (std::list<model_component_ref *> *)l, model_component_type_triangle );
    }

    //get all triangles belonging to group
    unsigned int model::getTrianglesByGroup( std::list<model_triangle_ref *> *l, dpid group_id )
    {
        return this->getComponentsByOwnerAndType( (std::list<model_component_ref *> *)l, group_id, model_component_type_triangle );
    }

    //release list returned by getTriangles()
    void model::releaseGetTriangles( std::list<model_triangle_ref *> *l )
    {
        model::releaseGetComponents( (std::list<model_component_ref *> *)l );
    }

    //create a triangle vertex
    model_triangle_vertex_ref *model::createTriangleVertex( dpthread_lock *thd, model_writelock *m, dpid triangle_id, dpid vertex_id )
    {
        model_triangle_vertex *o;
        dpid id;
        shared_obj_guard g;
        model_triangle_vertex_writelock *ol;

        id = thd->genId();
        o = new model_triangle_vertex( m, id, triangle_id, vertex_id );
        this->addComp( o, id, model_component_type_triangle_vertex, triangle_id, vertex_id );

        ol = (model_triangle_vertex_writelock *)g.writeLock( o );
        if( !ol )
            return 0;
        return (model_triangle_vertex_ref *)ol->getRef();
    }

    //find a triangle vertex by id
    model_triangle_vertex_ref *model::findTriangleVertex( dpid id )
    {
        return (model_triangle_vertex_ref *)this->find( id, model_component_type_triangle_vertex );
    }

    //get all triangle vertexes
    unsigned int model::getTriangleVertexes( std::list<model_triangle_vertex_ref *> *l )
    {
        return this->getComponentsByType( (std::list<model_component_ref *> *)l, model_component_type_triangle_vertex );
    }

    //get all triangle vertexes belonging to triangle
    unsigned int model::getTriangleVertexesByTriangle( std::list<model_triangle_vertex_ref *> *l, dpid triangle_id )
    {
        return this->getComponentsByOwnerAndType( (std::list<model_component_ref *> *)l, triangle_id, model_component_type_triangle_vertex );
    }

    //get all triangle vertexes belonging to vertex
    unsigned int model::getTriangleVertexesByVertex( std::list<model_triangle_vertex_ref *> *l, dpid vertex_id )
    {
        return this->getTriangleVertexesByTriangle( l, vertex_id );
    }

    //release list returned by getTriangleVertexes()
    void model::releaseGetTriangleVertexes( std::list<model_triangle_vertex_ref *> *l )
    {
        model::releaseGetComponents( (std::list<model_component_ref *> *)l );
    }

    //clear all components from model
    void model::clear( void )
    {
        this->deleteComps();
    }

    //create a material
    model_material_ref *model::createMaterial( dpthread_lock *thd, model_writelock *m )
    {
        model_material *o;
        dpid id;
        shared_obj_guard g;
        model_material_writelock *ol;

        id = thd->genId();
        o = new model_material( m, id );
        this->addComp( o, id, model_component_type_material );

        ol = (model_material_writelock *)g.writeLock( o );
        if( !ol )
            return 0;
        return (model_material_ref *)ol->getRef();
    }

    //find a material by id
    model_material_ref *model::findMaterial( dpid id )
    {
        return (model_material_ref *)this->find( id, model_component_type_material );
    }

    //get all materials
    unsigned int model::getMaterials( std::list<model_material_ref *> *l )
    {
        return this->getComponentsByType( (std::list<model_component_ref *> *)l, model_component_type_material );
    }

    //release list returned by getMateriales()
    void model::releaseGetMaterials( std::list<model_material_ref *> *l )
    {
        model::releaseGetComponents( (std::list<model_component_ref *> *)l );
    }

    //create a animation
    model_animation_ref *model::createAnimation( dpthread_lock *thd, model_writelock *m )
    {
        model_animation *o;
        dpid id;
        shared_obj_guard g;
        model_animation_writelock *ol;

        id = thd->genId();
        o = new model_animation( m, id );
        this->addComp( o, id, model_component_type_animation );

        ol = (model_animation_writelock *)g.writeLock( o );
        if( !ol )
            return 0;
        return (model_animation_ref *)ol->getRef();
    }

    //find a animation by id
    model_animation_ref *model::findAnimation( dpid id )
    {
        return (model_animation_ref *)this->find( id, model_component_type_animation );
    }

    //get all animations
    unsigned int model::getAnimations( std::list<model_animation_ref *> *l )
    {
        return this->getComponentsByType( (std::list<model_component_ref *> *)l, model_component_type_animation );
    }

    //release list returned by getAnimations()
    void model::releaseGetAnimations( std::list<model_animation_ref *> *l )
    {
        model::releaseGetComponents( (std::list<model_component_ref *> *)l );
    }

    //create a frame
    model_frame_ref *model::createFrame( dpthread_lock *thd, model_writelock *m )
    {
        model_frame *o;
        dpid id;
        shared_obj_guard g;
        model_frame_writelock *ol;

        id = thd->genId();
        o = new model_frame( m, id );
        this->addComp( o, id, model_component_type_frame );

        ol = (model_frame_writelock *)g.writeLock( o );
        if( !ol )
            return 0;
        return (model_frame_ref *)ol->getRef();
    }

    //find a frame by id
    model_frame_ref *model::findFrame( dpid id )
    {
        return (model_frame_ref *)this->find( id, model_component_type_frame );
    }

    //get all frames
    unsigned int model::getFrames( std::list<model_frame_ref *> *l )
    {
        return this->getComponentsByType( (std::list<model_component_ref *> *)l, model_component_type_frame );
    }

    //release list returned by getframes()
    void model::releaseGetFrames( std::list<model_frame_ref *> *l )
    {
        model::releaseGetComponents( (std::list<model_component_ref *> *)l );
    }

    //create a animation_frame
    model_animation_frame_ref *model::createAnimationFrame( dpthread_lock *thd, model_writelock *m, dpid animation_id, dpid frame_id, float ftime )
    {
        model_animation_frame *o;
        dpid id;
        shared_obj_guard g;
        model_animation_frame_writelock *ol;

        id = thd->genId();
        o = new model_animation_frame( m, id, animation_id, frame_id, ftime );
        this->addComp( o, id, model_component_type_animation_frame, animation_id );

        ol = (model_animation_frame_writelock *)g.writeLock( o );
        if( !ol )
            return 0;
        return (model_animation_frame_ref *)ol->getRef();
    }

    //find a animation_frame by id
    model_animation_frame_ref *model::findAnimationFrame( dpid id )
    {
        return (model_animation_frame_ref *)this->find( id, model_component_type_animation_frame );
    }

    //get all animation_frames
    unsigned int model::getAnimationFrames( std::list<model_animation_frame_ref *> *l )
    {
        return this->getComponentsByType( (std::list<model_component_ref *> *)l, model_component_type_animation_frame );
    }

    //get all animation_frames by animation id
    unsigned int model::getAnimationFramesByAnimation( std::list<model_animation_frame_ref *> *l, dpid anim_id )
    {
        return this->getComponentsByOwnerAndType( (std::list<model_component_ref *> *)l, anim_id, model_component_type_animation_frame );
    }

    //release list returned by getanimation_frames()
    void model::releaseGetAnimationFrames( std::list<model_animation_frame_ref *> *l )
    {
        model::releaseGetComponents( (std::list<model_component_ref *> *)l );
    }

    //create a joint frame
    model_frame_joint_ref *model::createFrameJoint( dpthread_lock *thd, model_writelock *m, dpid frame_id, dpid joint_id )
    {
        model_frame_joint *o;
        dpid id;
        shared_obj_guard g;
        model_frame_joint_writelock *ol;

        id = thd->genId();
        o = new model_frame_joint( m, id, frame_id, joint_id );
        this->addComp( o, id, model_component_type_frame_joint, frame_id, joint_id );

        ol = (model_frame_joint_writelock *)g.writeLock( o );
        if( !ol )
            return 0;
        return (model_frame_joint_ref *)ol->getRef();
    }

    //find a joint frame by id
    model_frame_joint_ref *model::findFrameJoint( dpid id )
    {
        return (model_frame_joint_ref *)this->find( id, model_component_type_frame_joint );
    }

    //get all joint frame
    unsigned int model::getFrameJoints( std::list<model_frame_joint_ref *> *l )
    {
        return this->getComponentsByType( (std::list<model_component_ref *> *)l, model_component_type_frame_joint );
    }

    //get all frame joints by frame id
    unsigned int model::getFrameJointsByFrame( std::list<model_frame_joint_ref *> *l, dpid frame_id )
    {
        return this->getComponentsByOwnerAndType( (std::list<model_component_ref *> *)l, frame_id, model_component_type_frame_joint );
    }

    //get all frame joints by joint id
    unsigned int model::getFrameJointsByJoint( std::list<model_frame_joint_ref *> *l, dpid joint_id )
    {
        return this->getComponentsByOwnerAndType( (std::list<model_component_ref *> *)l, joint_id, model_component_type_frame_joint );
    }

    //get all frame joints by joint and frame id
    unsigned int model::getFrameJointsByFrameAndJoint( std::list<model_frame_joint_ref *> *l, dpid frame_id, dpid joint_id )
    {
        return this->getComponentsByTwoOwnersAndType( (std::list<model_component_ref *> *)l, joint_id, frame_id, model_component_type_frame_joint );
    }

    //release list returned by getJointFrames()
    void model::releaseGetFrameJoints( std::list<model_frame_joint_ref *> *l )
    {
        model::releaseGetComponents( (std::list<model_component_ref *> *)l );
    }

    //create a joint
    model_joint_ref *model::createJoint( dpthread_lock *thd, model_writelock *m )
    {
        dpid i;
        dpid_zero( &i );
        return this->createJoint( thd, m, i );
    }

    //create a joint
    model_joint_ref *model::createJoint( dpthread_lock *thd, model_writelock *m, dpid parent_id )
    {
        model_joint *o;
        dpid id;
        shared_obj_guard g;
        model_joint_writelock *ol;

        id = thd->genId();
        o = new model_joint( m, id, parent_id );
        this->addComp( o, id, model_component_type_joint, parent_id );

        ol = (model_joint_writelock *)g.writeLock( o );
        if( !ol )
            return 0;
        return (model_joint_ref *)ol->getRef();
    }

    //find a joint by id
    model_joint_ref *model::findJoint( dpid id )
    {
        return (model_joint_ref *)this->find( id, model_component_type_joint );
    }

    //get all joints
    unsigned int model::getJoints( std::list<model_joint_ref *> *l )
    {
        return this->getComponentsByType( (std::list<model_component_ref *> *)l, model_component_type_joint );
    }

    //get all joints by parent
    unsigned int model::getJointsByParent( std::list<model_joint_ref *> *l, dpid parent_id )
    {
        return this->getComponentsByOwnerAndType( (std::list<model_component_ref *> *)l, parent_id, model_component_type_joint );
    }

    //release list returned by getJoint()
    void model::releaseGetJoints( std::list<model_joint_ref *> *l )
    {
        model::releaseGetComponents( (std::list<model_component_ref *> *)l );
    }

    //create a vertex joint
    model_vertex_joint_ref *model::createVertexJoint( dpthread_lock *thd, model_writelock *m, dpid vertex_id, dpid joint_id )
    {
        model_vertex_joint *o;
        dpid id;
        shared_obj_guard g;
        model_vertex_joint_writelock *ol;

        id = thd->genId();
        o = new model_vertex_joint( m, id, vertex_id, joint_id );
        this->addComp( o, id, model_component_type_vertex_joint, vertex_id, joint_id );

        ol = (model_vertex_joint_writelock *)g.writeLock( o );
        if( !ol )
            return 0;
        return (model_vertex_joint_ref *)ol->getRef();
    }

    //find a vertex joint by id
    model_vertex_joint_ref *model::findVertexJoint( dpid id )
    {
        return (model_vertex_joint_ref *)this->find( id, model_component_type_vertex_joint );
    }

    //get all vertex joints
    unsigned int model::getVertexJoints( std::list<model_vertex_joint_ref *> *l )
    {
        return this->getComponentsByType( (std::list<model_component_ref *> *)l, model_component_type_vertex_joint );
    }

    //get all vertex joints by vertex
    unsigned int model::getVertexJointsByVertex( std::list<model_vertex_joint_ref *> *l, dpid vertex_id )
    {
        return this->getComponentsByOwnerAndType( (std::list<model_component_ref *> *)l, vertex_id, model_component_type_vertex_joint );
    }

    //get all vertex joints by joint
    unsigned int model::getVertexJointsByJoint( std::list<model_vertex_joint_ref *> *l, dpid joint_id )
    {
        return this->getComponentsByOwnerAndType( (std::list<model_component_ref *> *)l, joint_id, model_component_type_vertex_joint );
    }

    //release list returned by getVertexJoints()
    void model::releaseGetVertexJoints( std::list<model_vertex_joint_ref *> *l )
    {
        model::releaseGetComponents( (std::list<model_component_ref *> *)l );
    }

    //returns default animation id
    dpid model::getDefaultAnimationId( void )
    {
        return this->default_anim_id;
    }

    //returns default animation
    model_animation_ref *model::getDefaultAnimation( void )
    {
        return this->findAnimation( this->default_anim_id );
    }

    //set default animation id
    void model::setDefaultAnimationId( dpid id )
    {
        this->default_anim_id = id;
    }

    //create model instance
    model_instance_ref *model::createInstance( dpthread_lock *thd, model_writelock *m )
    {
        model_instance *o;
        dpid id;
        shared_obj_guard g;
        model_instance_writelock *ol;

        id = thd->genId();
        o = new model_instance( thd, m, id );
        this->addComp( o, id, model_component_type_instance );

        ol = (model_instance_writelock *)g.writeLock( o );
        if( !ol )
            return 0;
        return (model_instance_ref *)ol->getRef();
    }

    //find model instance
    model_instance_ref *model::findInstance( dpid id )
    {
        return (model_instance_ref *)this->find( id, model_component_type_instance );
    }

    //get model instances
    unsigned int model::getInstances( std::list<model_instance_ref *> *l )
    {
        return this->getComponentsByType( (std::list<model_component_ref *> *)l, model_component_type_instance );
    }

    //release list returned by getInstances()
    void model::releaseGetInstances( std::list<model_instance_ref *> *l )
    {
        model::releaseGetComponents( (std::list<model_component_ref *> *)l );
    }

    //create group instance
    model_group_instance_ref *model::createGroupInstance( dpthread_lock *thd, model_writelock *m, dpid instance_id, dpid group_id, dpid parent_id )
    {
        model_group_instance *o;
        dpid id;
        shared_obj_guard g;
        model_group_instance_writelock *ol;

        id = thd->genId();
        o = new model_group_instance( m, id, instance_id, group_id, parent_id );
        this->addComp( o, id, model_component_type_group_instance, instance_id, group_id, parent_id );

        ol = (model_group_instance_writelock *)g.writeLock( o );
        if( !ol )
            return 0;
        return (model_group_instance_ref *)ol->getRef();
    }

    //find group instance
    model_group_instance_ref *model::findGroupInstance( dpid id )
    {
        return (model_group_instance_ref *)this->find( id, model_component_type_group_instance );
    }

    //get group instances by model instance id
    unsigned int model::getGroupInstancesByInstance( dpid instance_id, std::list<model_group_instance_ref *> *l )
    {
        return this->getComponentsByOwnerAndType( (std::list<model_component_ref *> *)l, instance_id, model_component_type_group_instance );
    }

    //get group instances by model instance id and parent group id
    unsigned int model::getGroupInstancesByInstanceAndParent( dpid instance_id, dpid parent_id, std::list<model_group_instance_ref *> *l )
    {
        return this->getComponentsByTwoOwnersAndType( (std::list<model_component_ref *> *)l, instance_id, parent_id, model_component_type_group_instance );
    }

    //release list returned by getGroupInstances()
    void model::releaseGetGroupInstances( std::list<model_group_instance_ref *> *l )
    {
        model::releaseGetComponents( (std::list<model_component_ref *> *)l );
    }

    //create triangle instance
    model_triangle_instance_ref *model::createTriangleInstance( dpthread_lock *thd, model_writelock *m, dpid instance_id, dpid triangle_id, dpid group_id )
    {
        model_triangle_instance *o;
        dpid id;
        shared_obj_guard g;
        model_triangle_instance_writelock *ol;

        id = thd->genId();
        o = new model_triangle_instance( m, id, instance_id, triangle_id, group_id );
        this->addComp( o, id, model_component_type_triangle_instance, instance_id, triangle_id, group_id );

        ol = (model_triangle_instance_writelock *)g.writeLock( o );
        if( !ol )
            return 0;
        return (model_triangle_instance_ref *)ol->getRef();
    }

    //find triangle instance
    model_triangle_instance_ref *model::findTriangleInstance( dpid id )
    {
        return (model_triangle_instance_ref *)this->find( id, model_component_type_triangle_instance );
    }

    //get group instances by model instance id
    unsigned int model::getTriangleInstancesByInstance( dpid instance_id, std::list<model_triangle_instance_ref *> *l )
    {
        return this->getComponentsByOwnerAndType( (std::list<model_component_ref *> *)l, instance_id, model_component_type_triangle_instance );
    }

    //get triangle instances by model instance id and parent group id
    unsigned int model::getTriangleInstancesByInstanceAndGroup( dpid instance_id, dpid group_id, std::list<model_triangle_instance_ref *> *l )
    {
        return this->getComponentsByTwoOwnersAndType( (std::list<model_component_ref *> *)l, instance_id, group_id, model_component_type_triangle_instance );
    }

    //release list returned by getTriangleInstances()
    void model::releaseGetTriangleInstances( std::list<model_triangle_instance_ref *> *l )
    {
        model::releaseGetComponents( (std::list<model_component_ref *> *)l );
    }

    //create triangle vertex instance
    model_triangle_vertex_instance_ref *model::createTriangleVertexInstance( dpthread_lock *thd, model_writelock *m, dpid instance_id, dpid triangle_vertex_id, dpid triangle_id, dpid vertex_id )
    {
        model_triangle_vertex_instance *o;
        dpid id;
        shared_obj_guard g;
        model_triangle_vertex_instance_writelock *ol;

        id = thd->genId();
        o = new model_triangle_vertex_instance( m, id, instance_id, triangle_vertex_id, triangle_id, vertex_id );
        this->addComp( o, id, model_component_type_triangle_vertex_instance, instance_id, triangle_vertex_id, triangle_id, vertex_id );

        ol = (model_triangle_vertex_instance_writelock *)g.writeLock( o );
        if( !ol )
            return 0;
        return (model_triangle_vertex_instance_ref *)ol->getRef();
    }

    //find triangle vertex instance
    model_triangle_vertex_instance_ref *model::findTriangleVertexInstance( dpid id )
    {
        return (model_triangle_vertex_instance_ref *)this->find( id, model_component_type_triangle_vertex_instance );
    }

    //get triangle vertex instances by model instance id
    unsigned int model::getTriangleVertexInstancesByInstance( dpid instance_id, std::list<model_triangle_vertex_instance_ref *> *l )
    {
        return this->getComponentsByOwnerAndType( (std::list<model_component_ref *> *)l, instance_id, model_component_type_triangle_vertex_instance );
    }

    //get triangle vertex instances by model instance id and parent triangle id
    unsigned int model::getTriangleVertexInstancesByInstanceAndTriangle( dpid instance_id, dpid triangle_id, std::list<model_triangle_vertex_instance_ref *> *l )
    {
        return this->getComponentsByTwoOwnersAndType( (std::list<model_component_ref *> *)l, instance_id, triangle_id, model_component_type_triangle_vertex_instance );
    }

    //release list returned by getTriangleVertexInstances()
    void model::releaseGetTriangleVertexInstances( std::list<model_triangle_vertex_instance_ref *> *l )
    {
        model::releaseGetComponents( (std::list<model_component_ref *> *)l );
    }

    //create vertex instance
    model_vertex_instance_ref *model::createVertexInstance( dpthread_lock *thd, model_writelock *m, dpid instance_id, dpid vertex_id )
    {
        model_vertex_instance *o;
        dpid id;
        shared_obj_guard g;
        model_vertex_instance_writelock *ol;

        id = thd->genId();
        o = new model_vertex_instance( m, id, instance_id, vertex_id );
        this->addComp( o, id, model_component_type_vertex_instance, instance_id, vertex_id );

        ol = (model_vertex_instance_writelock *)g.writeLock( o );
        if( !ol )
            return 0;
        return (model_vertex_instance_ref *)ol->getRef();
    }

    //find vertex instance
    model_vertex_instance_ref *model::findVertexInstance( dpid id )
    {
        return (model_vertex_instance_ref *)this->find( id, model_component_type_vertex_instance );
    }

    //get  vertex instances by model instance id
    unsigned int model::getVertexInstancesByInstance( dpid instance_id, std::list<model_vertex_instance_ref *> *l )
    {
        return this->getComponentsByOwnerAndType( (std::list<model_component_ref *> *)l, instance_id, model_component_type_vertex_instance );
    }

    //get  vertex instances by model instance and vertex id
    unsigned int model::getVertexInstancesByInstanceAndVertex( dpid instance_id, dpid vertex_id, std::list<model_vertex_instance_ref *> *l )
    {
        return this->getComponentsByTwoOwnersAndType( (std::list<model_component_ref *> *)l, instance_id, vertex_id, model_component_type_vertex_instance );
    }

    //release list returned by getVertexInstances()
    void model::releaseGetVertexInstances( std::list<model_vertex_instance_ref *> *l )
    {
        model::releaseGetComponents( (std::list<model_component_ref *> *)l );
    }

};
