
#include "model_instances.h"
#include "../models.h"
#include "../../../renderer/renderer_model_instance/renderer_model_instance_ref.h"
#include "../../../renderer/renderer_model_instance/renderer_model_instance_readlock.h"
#include "../model_group_instance/model_group_instances.h"
#include "../model_group/model_groups.h"
#include "../model_triangle_instance/model_triangle_instances.h"
#include "../model_triangle/model_triangles.h"
#include "../model_animation/model_animations.h"
#include "../model_animation_instance/model_animation_instances.h"
#include "../model_joint/model_joints.h"
#include "../model_joint_instance/model_joint_instances.h"

namespace dragonpoop
{

    //ctor
    model_instance::model_instance( dpthread_lock *thd, model_writelock *ml, dpid id ) : model_component( ml, id,model_component_type_instance, 30 )
    {
        this->r = 0;
        this->makeAnimations( thd, ml );
        this->makeJoints( thd, ml );
        this->makeGroups( thd, ml );
        this->makeTriangles( thd, ml );
    }

    //dtor
    model_instance::~model_instance( void )
    {
        delete this->r;
        this->killTriangles();
        this->killGroups();
        this->killJoints();
        this->killAnimations();
    }

    //generate read lock
    shared_obj_readlock *model_instance::genReadLock( shared_obj *p, dpmutex_readlock *l )
    {
        return new model_instance_readlock( (model_instance *)p, l );
    }

    //generate write lock
    shared_obj_writelock *model_instance::genWriteLock( shared_obj *p, dpmutex_writelock *l )
    {
        return new model_instance_writelock( (model_instance *)p, l );
    }

    //generate ref
    shared_obj_ref *model_instance::genRef( shared_obj *p, std::shared_ptr<shared_obj_refkernal> *k )
    {
        return new model_instance_ref( (model_instance *)p, k );
    }

    //do background processing
    void model_instance::onRun( dpthread_lock *thd, gfx_writelock *g, model_writelock *m, model_component_writelock *l )
    {
        renderer_model_instance_readlock *rl;
        shared_obj_guard o;

        this->syncAnimations( thd, m );
        this->syncJoints( thd, m );
        this->syncTriangles( m );
        this->syncGroups( m );

        if( !this->r )
            return;
        rl = (renderer_model_instance_readlock *)o.tryReadLock( this->r, 20 );
        if( !rl )
            return;
        rl->update();
    }

    //returns true if has renderer
    bool model_instance::hasRenderer( void )
    {
        if( !this->r || !this->r->isLinked() )
            return 0;
        return 1;
    }

    //set renderer
    void model_instance::setRenderer( shared_obj_writelock *r )
    {
        if( this->r )
            delete this->r;
        this->r = r->getRef();
    }

    //get renderer
    shared_obj_ref *model_instance::getRenderer( void )
    {
        shared_obj_writelock *l;
        shared_obj_guard o;
        if( !this->r )
            return 0;
        l = o.writeLock( this->r );
        if( !l )
            return 0;
        return l->getRef();
    }

    //create group instances
    void model_instance::makeGroups( dpthread_lock *thd, model_writelock *ml )
    {
        std::list<model_group_ref *> l;
        std::list<model_group_ref *>::iterator i;
        model_group_ref *p;
        model_group_readlock *pl;
        model_group_instance_ref *r;
        shared_obj_guard o;

        ml->getGroups( &l );

        for( i = l.begin(); i != l.end(); ++i )
        {
            p = *i;
            pl = (model_group_readlock *)o.readLock( p );
            r = ml->createGroupInstance( thd, this->getId(), pl->getId(), pl->getParentId(), pl->getMaterialId() );
            delete r;
        }

        ml->releaseGetGroups( &l );
    }

    //destroy group instances
    void model_instance::killGroups( void )
    {
        std::list<model_group_instance_ref *> l;
        std::list<model_group_instance_ref *>::iterator i;
        model_group_instance_ref *p;
        model_group_instance_writelock *pl;
        shared_obj_guard o;

        this->getGroups( &l );

        for( i = l.begin(); i != l.end(); ++i )
        {
            p = *i;
            pl = (model_group_instance_writelock *)o.writeLock( p );
            pl->kill();
        }

        model_instance::releaseGetGroups( &l );
    }

    //sync group instances
    void model_instance::syncGroups( model_writelock *ml )
    {
        std::list<model_group_instance_ref *> l;
        std::list<model_group_instance_ref *>::iterator i;
        model_group_instance_ref *p;
        model_group_instance_writelock *pl;
        shared_obj_guard o;

        this->getGroups( &l );

        for( i = l.begin(); i != l.end(); ++i )
        {
            p = *i;
            pl = (model_group_instance_writelock *)o.tryWriteLock( p, 30 );
            if( pl )
                pl->sync( ml );
        }

        model_instance::releaseGetGroups( &l );
    }

    //get group instances
    unsigned int model_instance::getGroups( std::list<model_group_instance_ref *> *l )
    {
        model_readlock *ml;
        model_ref *m;
        shared_obj_guard o;

        m = this->getModel();
        if( !m )
            return 0;
        ml = (model_readlock *)o.readLock( m );
        delete m;
        if( !ml )
            return 0;

        return ml->getGroupInstancesByInstance( this->getId(), l );
    }

    //get group instances by parent
    unsigned int model_instance::getGroupsByParent( dpid parent_id, std::list<model_group_instance_ref *> *l )
    {
        model_readlock *ml;
        model_ref *m;
        shared_obj_guard o;

        m = this->getModel();
        if( !m )
            return 0;
        ml = (model_readlock *)o.readLock( m );
        delete m;
        if( !ml )
            return 0;

        return ml->getGroupInstancesByInstanceAndParent( this->getId(), parent_id, l );
    }

    //release list returned by getGroups()
    void model_instance::releaseGetGroups( std::list<model_group_instance_ref *> *l )
    {
        model::releaseGetGroupInstances( l );
    }

    //create triangle instances
    void model_instance::makeTriangles( dpthread_lock *thd, model_writelock *ml )
    {
        std::list<model_triangle_ref *> l;
        std::list<model_triangle_ref *>::iterator i;
        model_triangle_ref *p;
        model_triangle_readlock *pl;
        model_triangle_instance_ref *r;
        shared_obj_guard o;

        ml->getTriangles( &l );

        for( i = l.begin(); i != l.end(); ++i )
        {
            p = *i;
            pl = (model_triangle_readlock *)o.readLock( p );
            r = ml->createTriangleInstance( thd, this->getId(), pl->getId(), pl->getParentId() );
            delete r;
        }

        ml->releaseGetTriangles( &l );
    }

    //destroy triangle instances
    void model_instance::killTriangles( void )
    {
        std::list<model_triangle_instance_ref *> l;
        std::list<model_triangle_instance_ref *>::iterator i;
        model_triangle_instance_ref *p;
        model_triangle_instance_writelock *pl;
        shared_obj_guard o;

        this->getTriangles( &l );

        for( i = l.begin(); i != l.end(); ++i )
        {
            p = *i;
            pl = (model_triangle_instance_writelock *)o.writeLock( p );
            pl->kill();
        }

        model_instance::releaseGetTriangles( &l );
    }

    //sync triangle instances
    void model_instance::syncTriangles( model_writelock *ml )
    {
        std::list<model_triangle_instance_ref *> l;
        std::list<model_triangle_instance_ref *>::iterator i;
        model_triangle_instance_ref *p;
        model_triangle_instance_writelock *pl;
        shared_obj_guard o;

        this->getTriangles( &l );

        for( i = l.begin(); i != l.end(); ++i )
        {
            p = *i;
            pl = (model_triangle_instance_writelock *)o.writeLock( p );
            pl->sync( ml );
        }

        model_instance::releaseGetTriangles( &l );
    }

    //get triangle instances
    unsigned int model_instance::getTriangles( std::list<model_triangle_instance_ref *> *l )
    {
        model_readlock *ml;
        model_ref *m;
        shared_obj_guard o;

        m = this->getModel();
        if( !m )
            return 0;
        ml = (model_readlock *)o.readLock( m );
        delete m;
        if( !ml )
            return 0;

        return ml->getTriangleInstancesByInstance( this->getId(), l );
    }

    //get triangle instances by group
    unsigned int model_instance::getTrianglesByGroup( dpid group_id, std::list<model_triangle_instance_ref *> *l )
    {
        model_readlock *ml;
        model_ref *m;
        shared_obj_guard o;

        m = this->getModel();
        if( !m )
            return 0;
        ml = (model_readlock *)o.readLock( m );
        delete m;
        if( !ml )
            return 0;

        return ml->getTriangleInstancesByInstanceAndGroup( this->getId(), group_id, l );
    }

    //release list returned by getTriangles()
    void model_instance::releaseGetTriangles( std::list<model_triangle_instance_ref *> *l )
    {
        model::releaseGetTriangleInstances( l );
    }

    //create animation instances
    void model_instance::makeAnimations( dpthread_lock *thd, model_writelock *ml )
    {
        std::list<model_animation_ref *> l;
        std::list<model_animation_ref *>::iterator i;
        model_animation_ref *p;
        model_animation_readlock *pl;
        model_animation_instance_ref *r;
        shared_obj_guard o;

        ml->getAnimations( &l );

        for( i = l.begin(); i != l.end(); ++i )
        {
            p = *i;
            pl = (model_animation_readlock *)o.readLock( p );
            r = ml->createAnimationInstance( thd, this->getId(), pl->getId() );
            delete r;
        }

        ml->releaseGetAnimations( &l );
    }

    //destroy animation instances
    void model_instance::killAnimations( void )
    {
        std::list<model_animation_instance_ref *> l;
        std::list<model_animation_instance_ref *>::iterator i;
        model_animation_instance_ref *p;
        model_animation_instance_writelock *pl;
        shared_obj_guard o;

        this->getAnimations( &l );

        for( i = l.begin(); i != l.end(); ++i )
        {
            p = *i;
            pl = (model_animation_instance_writelock *)o.writeLock( p );
            pl->kill();
        }

        model_instance::releaseGetAnimations( &l );
    }

    //sync animation instances
    void model_instance::syncAnimations( dpthread_lock *thd, model_writelock *ml )
    {
        std::list<model_animation_instance_ref *> l;
        std::list<model_animation_instance_ref *>::iterator i;
        model_animation_instance_ref *p;
        model_animation_instance_writelock *pl;
        shared_obj_guard o;

        this->getAnimations( &l );

        for( i = l.begin(); i != l.end(); ++i )
        {
            p = *i;
            pl = (model_animation_instance_writelock *)o.writeLock( p );
            pl->sync( thd, ml );
        }

        model_instance::releaseGetAnimations( &l );
    }

    //get animation instances
    unsigned int model_instance::getAnimations( std::list<model_animation_instance_ref *> *l )
    {
        model_readlock *ml;
        model_ref *m;
        shared_obj_guard o;

        m = this->getModel();
        if( !m )
            return 0;
        ml = (model_readlock *)o.readLock( m );
        delete m;
        if( !ml )
            return 0;

        return ml->getAnimationInstancesByInstance( this->getId(), l );
    }

    //release list returned by getAnimations()
    void model_instance::releaseGetAnimations( std::list<model_animation_instance_ref *> *l )
    {
        model::releaseGetAnimationInstances( l );
    }

    //create joint instances
    void model_instance::makeJoints( dpthread_lock *thd, model_writelock *ml )
    {
        std::list<model_joint_ref *> l;
        std::list<model_joint_ref *>::iterator i;
        model_joint_ref *p;
        model_joint_readlock *pl;
        model_joint_instance_ref *r;
        shared_obj_guard o;

        ml->getJoints( &l );

        for( i = l.begin(); i != l.end(); ++i )
        {
            p = *i;
            pl = (model_joint_readlock *)o.readLock( p );
            r = ml->createJointInstance( thd, this->getId(), pl->getId() );
            delete r;
        }

        ml->releaseGetJoints( &l );
    }

    //destroy joint instances
    void model_instance::killJoints( void )
    {
        std::list<model_joint_instance_ref *> l;
        std::list<model_joint_instance_ref *>::iterator i;
        model_joint_instance_ref *p;
        model_joint_instance_writelock *pl;
        shared_obj_guard o;

        this->getJoints( &l );

        for( i = l.begin(); i != l.end(); ++i )
        {
            p = *i;
            pl = (model_joint_instance_writelock *)o.writeLock( p );
            pl->kill();
        }

        model_instance::releaseGetJoints( &l );
    }

    //sync joint instances
    void model_instance::syncJoints( dpthread_lock *thd, model_writelock *ml )
    {
        std::list<model_joint_instance_ref *> l;
        std::list<model_joint_instance_ref *>::iterator i;
        model_joint_instance_ref *p;
        model_joint_instance_writelock *pl;
        shared_obj_guard o;

        this->getJoints( &l );

        for( i = l.begin(); i != l.end(); ++i )
        {
            p = *i;
            pl = (model_joint_instance_writelock *)o.writeLock( p );
            pl->sync( thd, ml );
        }

        model_instance::releaseGetJoints( &l );
    }

    //get joint instances
    unsigned int model_instance::getJoints( std::list<model_joint_instance_ref *> *l )
    {
        model_readlock *ml;
        model_ref *m;
        shared_obj_guard o;

        m = this->getModel();
        if( !m )
            return 0;
        ml = (model_readlock *)o.readLock( m );
        delete m;
        if( !ml )
            return 0;

        return ml->getJointInstancesByInstance( this->getId(), l );
    }

    //release list returned by getJoints()
    void model_instance::releaseGetJoints( std::list<model_joint_instance_ref *> *l )
    {
        model::releaseGetJointInstances( l );
    }

};
