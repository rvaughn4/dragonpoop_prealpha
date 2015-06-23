
#include "model_animation_frame.h"
#include "model_animation_frame_ref.h"
#include "model_animation_frame_readlock.h"
#include "model_animation_frame_writelock.h"
#include "../model_ref.h"
#include "../model_readlock.h"

namespace dragonpoop
{

    //ctor
    model_animation_frame::model_animation_frame( model_writelock *ml, dpid id, dpid animation_id, dpid frame_id, float ftime ) : model_component( ml, id, model_component_type_animation_frame, 0 )
    {
        this->animation_id = animation_id;
        this->frame_id = frame_id;
        this->time = ftime;
    }

    //dtor
    model_animation_frame::~model_animation_frame( void )
    {
        model_component_writelock *l;
        shared_obj_guard g;

        l = (model_component_writelock *)g.writeLock( this );
        g.unlock();
    }

    //generate read lock
    shared_obj_readlock *model_animation_frame::genReadLock( shared_obj *p, dpmutex_readlock *l )
    {
        return new model_animation_frame_readlock( (model_animation_frame *)p, l );
    }

    //generate write lock
    shared_obj_writelock *model_animation_frame::genWriteLock( shared_obj *p, dpmutex_writelock *l )
    {
        return new model_animation_frame_writelock( (model_animation_frame *)p, l );
    }

    //generate ref
    shared_obj_ref *model_animation_frame::genRef( shared_obj *p, std::shared_ptr<shared_obj_refkernal> *k )
    {
        return new model_animation_frame_ref( (model_animation_frame *)p, k );
    }

    //do background processing
    void model_animation_frame::onRun( dpthread_lock *thd, gfx_writelock *g, model_writelock *m, model_component_writelock *l )
    {

    }

    //returns animation id
    dpid model_animation_frame::getAnimationId( void )
    {
        return this->animation_id;
    }

    //returns animation
    model_animation_ref *model_animation_frame::getAnimation( void )
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
        return ml->findAnimation( this->animation_id );
    }

    //returns frame id
    dpid model_animation_frame::getFrameId( void )
    {
        return this->frame_id;
    }

    //returns frame
    model_frame_ref *model_animation_frame::getFrame( void )
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

    //returns time
    float model_animation_frame::getTime( void )
    {
        return this->time;
    }

    //sets time
    void model_animation_frame::setTime( float f )
    {
        this->time = f;
    }

};
