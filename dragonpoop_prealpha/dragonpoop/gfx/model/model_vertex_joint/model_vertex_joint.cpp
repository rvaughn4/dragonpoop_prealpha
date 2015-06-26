
#include "model_vertex_joint.h"
#include "model_vertex_joint_ref.h"
#include "model_vertex_joint_readlock.h"
#include "model_vertex_joint_writelock.h"
#include "../model_ref.h"
#include "../model_readlock.h"

namespace dragonpoop
{

    //ctor
    model_vertex_joint::model_vertex_joint( model_writelock *ml, dpid id, dpid vertex_id, dpid joint_id ) : model_component( ml, id, model_component_type_vertex_joint, 0 )
    {
        this->joint_id = joint_id;
        this->vertex_id = vertex_id;
    }

    //dtor
    model_vertex_joint::~model_vertex_joint( void )
    {
        model_component_writelock *l;
        shared_obj_guard g;

        l = (model_component_writelock *)g.writeLock( this );
        g.unlock();
    }

    //generate read lock
    shared_obj_readlock *model_vertex_joint::genReadLock( shared_obj *p, dpmutex_readlock *l )
    {
        return new model_vertex_joint_readlock( (model_vertex_joint *)p, l );
    }

    //generate write lock
    shared_obj_writelock *model_vertex_joint::genWriteLock( shared_obj *p, dpmutex_writelock *l )
    {
        return new model_vertex_joint_writelock( (model_vertex_joint *)p, l );
    }

    //generate ref
    shared_obj_ref *model_vertex_joint::genRef( shared_obj *p, std::shared_ptr<shared_obj_refkernal> *k )
    {
        return new model_vertex_joint_ref( (model_vertex_joint *)p, k );
    }

    //do background processing
    void model_vertex_joint::onRun( dpthread_lock *thd, gfx_writelock *g, model_writelock *m, model_component_writelock *l )
    {

    }

    //returns animation id
    dpid model_vertex_joint::getJointId( void )
    {
        return this->joint_id;
    }

    //returns animation
    model_joint_ref *model_vertex_joint::getJoint( void )
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
        return ml->findJoint( this->joint_id );
    }

    //returns vertex id
    dpid model_vertex_joint::getVertexId( void )
    {
        return this->vertex_id;
    }

    //returns vertex
    model_vertex_ref *model_vertex_joint::getVertex( void )
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
        return ml->findVertex( this->vertex_id );
    }

    //returns weight
    float model_vertex_joint::getWeight( void )
    {
        return this->weight;
    }

    //sets weight
    void model_vertex_joint::setWeight( float w )
    {
        this->weight = w;
    }


};
