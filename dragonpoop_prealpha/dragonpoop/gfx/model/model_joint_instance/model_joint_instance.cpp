
#include "model_joint_instance.h"
#include "model_joint_instance_readlock.h"
#include "model_joint_instance_writelock.h"
#include "model_joint_instance_ref.h"
#include "../model_animation_instance/model_animation_instance_readlock.h"
#include "../model_animation_instance/model_animation_instance_ref.h"
#include "../model_frame_joint/model_frame_joint_readlock.h"
#include "../model_frame_joint/model_frame_joint_ref.h"
#include "../../../core/dpthread/dpthread_lock.h"
#include "../model_writelock.h"

namespace dragonpoop
{

    //ctor
    model_joint_instance::model_joint_instance( dpthread_lock *thd, model_writelock *ml, dpid id, dpid instance_id, dpid joint_id ) : model_component( ml, id,model_component_type_joint_instance, 0 )
    {

        memset( &this->final, 0, sizeof( this->final ) );
        memset( this->perAnims, 0, sizeof( this->perAnims ) );

        this->instance_id = instance_id;
        this->joint_id = joint_id;
        this->sync( thd, ml );
    }

    //dtor
    model_joint_instance::~model_joint_instance( void )
    {

    }

    //generate read lock
    shared_obj_readlock *model_joint_instance::genReadLock( shared_obj *p, dpmutex_readlock *l )
    {
        return new model_joint_instance_readlock( (model_joint_instance *)p, l );
    }

    //generate write lock
    shared_obj_writelock *model_joint_instance::genWriteLock( shared_obj *p, dpmutex_writelock *l )
    {
        return new model_joint_instance_writelock( (model_joint_instance *)p, l );
    }

    //generate ref
    shared_obj_ref *model_joint_instance::genRef( shared_obj *p, std::shared_ptr<shared_obj_refkernal> *k )
    {
        return new model_joint_instance_ref( (model_joint_instance *)p, k );
    }

    //do background processing
    void model_joint_instance::onRun( dpthread_lock *thd, gfx_writelock *g, model_writelock *m, model_component_writelock *l )
    {

    }

    //return instance id
    dpid model_joint_instance::getInstanceId( void )
    {
        return this->instance_id;
    }

    //return joint id
    dpid model_joint_instance::getJointId( void )
    {
        return this->joint_id;
    }

    //sync joint
    void model_joint_instance::sync( dpthread_lock *thd, model_writelock *ml )
    {
        std::list<model_animation_instance_ref *> l;
        std::list<model_animation_instance_ref *>::iterator i;
        model_animation_instance_ref *p;
        model_animation_instance_readlock *pl;
        shared_obj_guard o;

        ml->getAnimationInstancesByInstance( this->instance_id, &l );

        for( i = l.begin(); i != l.end(); ++i )
        {
            p = *i;
            pl = (model_animation_instance_readlock *)o.tryReadLock( p, 100 );
            if( !pl )
                continue;
            this->processAnim( thd, ml, pl );
        }

        ml->releaseGetAnimationInstances( &l );
    }

    //get translation for this joint
    void model_joint_instance::getTranslation( dpxyzw *x )
    {
        *x = this->final.end.trans;
    }

    //get rotation for this joint
    void model_joint_instance::getRotation( dpxyzw *x )
    {
        *x = this->final.end.rot;
    }

    //get animation time for this joint
    uint64_t model_joint_instance::getTime( void )
    {
        return this->final.end.time;
    }

    //find animation data
    model_joint_instance_anim *model_joint_instance::findAnim( dpid anim_id )
    {
        unsigned int i;
        model_joint_instance_anim *fr, *p;

        fr = 0;
        for( i = 0; i < model_joint_instance_anim_max; i++ )
        {
            p = &this->perAnims[ i ];
            if( dpid_isZero( &p->anim_id ) )
            {
                fr = p;
                continue;
            }
            if( dpid_compare( &p->anim_id, &anim_id ) )
                return p;
        }

        if( fr )
        {
            memset( fr, 0, sizeof(model_joint_instance_anim) );
            fr->anim_id = anim_id;
        }

        return fr;
    }

    //process animation
    void model_joint_instance::processAnim( dpthread_lock *thd, model_writelock *ml, model_animation_instance_readlock *a )
    {
        model_joint_instance_anim *dat;
        std::list<model_frame_joint_ref *> l;
        std::list<model_frame_joint_ref *>::iterator i;
        model_frame_joint_ref *f;
        model_frame_joint_readlock *fl;
        shared_obj_guard o;
        float dr, dr1;
        uint64_t t;

        dat = this->findAnim( a->getAnimationId() );
        if( !dat )
            return;

        t = thd->getTicks();
        if( dat->start.time != dat->end.time )
            dr = (float)( t - dat->start.time ) / (float)( dat->end.time - dat->start.time );
        else
            dr = 0;
        if( dr > 1.0f )
            dr = 1.0f;
        dr1 = 1.0f - dr;

        dat->start.trans.x = dat->start.trans.x * dr1 + dat->end.trans.x * dr;
        dat->start.trans.y = dat->start.trans.y * dr1 + dat->end.trans.y * dr;
        dat->start.trans.z = dat->start.trans.z * dr1 + dat->end.trans.z * dr;
        dat->start.trans.w = dat->start.trans.w * dr1 + dat->end.trans.w * dr;

        dat->start.rot.x = dat->start.rot.x * dr1 + dat->end.rot.x * dr;
        dat->start.rot.y = dat->start.rot.y * dr1 + dat->end.rot.y * dr;
        dat->start.rot.z = dat->start.rot.z * dr1 + dat->end.rot.z * dr;
        dat->start.rot.w = dat->start.rot.w * dr1 + dat->end.rot.w * dr;

        memset( &dat->end, 0, sizeof( dat->end ) );
        dat->start.time = t;
        dat->end.time = a->getCurrentFrameTime();

        ml->getFrameJointsByFrameAndJoint( &l, a->getCurrentFrameId(), this->getJointId() );

        for( i = l.begin(); i != l.end(); ++i )
        {
            f = *i;
            fl = (model_frame_joint_readlock *)o.tryReadLock( f, 100 );
            if( !fl )
                continue;
            fl->getPosition( &dat->end.trans );
            fl->getRotation( &dat->end.rot );
        }

        ml->releaseGetFrameJoints( &l );
    }

};
