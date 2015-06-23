
#include "model_frame_joint.h"
#include "model_frame_joint_ref.h"
#include "model_frame_joint_readlock.h"
#include "model_frame_joint_writelock.h"
#include "../model_ref.h"
#include "../model_readlock.h"

namespace dragonpoop
{

    //ctor
    model_frame_joint::model_frame_joint( model_writelock *ml, dpid id, dpid frame_id, dpid joint_id ) : model_component( ml, id, model_component_type_frame_joint, 0 )
    {
        this->joint_id = joint_id;
        this->frame_id = frame_id;
    }

    //dtor
    model_frame_joint::~model_frame_joint( void )
    {
        model_component_writelock *l;
        shared_obj_guard g;

        l = (model_component_writelock *)g.writeLock( this );
        g.unlock();
    }

    //generate read lock
    shared_obj_readlock *model_frame_joint::genReadLock( shared_obj *p, dpmutex_readlock *l )
    {
        return new model_frame_joint_readlock( (model_frame_joint *)p, l );
    }

    //generate write lock
    shared_obj_writelock *model_frame_joint::genWriteLock( shared_obj *p, dpmutex_writelock *l )
    {
        return new model_frame_joint_writelock( (model_frame_joint *)p, l );
    }

    //generate ref
    shared_obj_ref *model_frame_joint::genRef( shared_obj *p, std::shared_ptr<shared_obj_refkernal> *k )
    {
        return new model_frame_joint_ref( (model_frame_joint *)p, k );
    }

    //do background processing
    void model_frame_joint::onRun( dpthread_lock *thd, gfx_writelock *g, model_writelock *m, model_component_writelock *l )
    {

    }

    //returns animation id
    dpid model_frame_joint::getJointId( void )
    {
        return this->joint_id;
    }

    //returns animation
    model_joint_ref *model_frame_joint::getJoint( void )
    {
        shared_obj_guard g;
        model_readlock *ml;
        model_ref *mr;

        mr = this->getModel();
        if( !mr )
            return 0;
        ml = (model_readlock *)g.readLock( mr );
        delete mr;
        if( !ml )
            return 0;
        return 0;//ml->findJoint( this->joint_id );
    }

    //returns frame id
    dpid model_frame_joint::getFrameId( void )
    {
        return this->frame_id;
    }

    //returns frame
    model_frame_ref *model_frame_joint::getFrame( void )
    {
        shared_obj_guard g;
        model_readlock *ml;
        model_ref *mr;

        mr = this->getModel();
        if( !mr )
            return 0;
        ml = (model_readlock *)g.readLock( mr );
        delete mr;
        if( !ml )
            return 0;
        return ml->findFrame( this->frame_id );
    }

    //get position
    void model_frame_joint::getPosition( dpxyzw *p )
    {
        *p = this->pos;
    }

    //get roatation
    void model_frame_joint::getRotation( dpxyzw *p )
    {
        *p = this->rot;
    }

    //set position
    void model_frame_joint::setPosition( dpxyzw *p )
    {
        this->pos = *p;
    }

    //set roatation
    void model_frame_joint::setRotation( dpxyzw *p )
    {
        this->rot = *p;
    }

};
