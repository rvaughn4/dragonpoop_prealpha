
#include "renderer.h"
#include "../core/core.h"
#include "../core/dptask/dptasks.h"
#include "renderer_task.h"
#include "renderer_readlock.h"
#include "renderer_writelock.h"
#include "renderer_ref.h"
#include "../core/dpthread/dpthread_lock.h"
#include "../core/dptaskpool/dptaskpool_writelock.h"

#include <iostream>
#include <thread>

namespace dragonpoop
{

    //ctor
    renderer::renderer( core *c, dptaskpool_writelock *tp ) : shared_obj( c->getMutexMaster() )
    {
        this->c = c;
        this->bDoRun = 1;
        this->bIsRun = 0;
        this->gtsk = new renderer_task( this );
        this->tsk = new dptask( c->getMutexMaster(), this->gtsk, 3, 1 );
        tp->addTask( this->tsk );
    }

    //dtor
    renderer::~renderer( void )
    {
        this->_kill();
        delete this->tsk;
        delete this->gtsk;
    }

    //stop task and deinit api
    void renderer::_kill( void )
    {
        volatile bool d;

        this->bDoRun = 0;
        d = this->bIsRun;
        while( d )
        {
            std::this_thread::sleep_for( std::chrono::milliseconds( 1 ) );
            d = this->bIsRun;
        }
    }

    //returns true if running
    bool renderer::isRunning( void )
    {
        if( !this->tsk )
            return 0;
        return this->bIsRun;
    }

    //return core
    core *renderer::getCore( void )
    {
        return this->c;
    }

    //generate read lock
    shared_obj_readlock *renderer::genReadLock( shared_obj *p, dpmutex_readlock *l )
    {
        return new renderer_readlock( (renderer *)p, l );
    }

    //generate write lock
    shared_obj_writelock *renderer::genWriteLock( shared_obj *p, dpmutex_writelock *l )
    {
        return new renderer_writelock( (renderer *)p, l );
    }

    //generate ref
    shared_obj_ref *renderer::genRef( shared_obj *p, std::shared_ptr<shared_obj_refkernal> *k )
    {
        return new renderer_ref( (renderer *)p, k );
    }

    //stop renderer task
    void renderer::kill( void )
    {
        this->bDoRun = 0;
    }

    //run renderer from task
    void renderer::run( dptask_writelock *tskl, dpthread_lock *thd )
    {
        if( this->bIsRun )
        {
            if( !this->bDoRun )
            {
                this->deinitApi();
                this->bIsRun = 0;
                tskl->kill();
                return;
            }

            if( !this->runApi() )
                this->bDoRun = 0;
            else
            {
                this->setViewport( this->getWidth(), this->getHeight() );
#define randcolor (float)rand() / (float)RAND_MAX
                this->clearScreen( randcolor, randcolor, randcolor );
                this->prepareWorldRender();
                this->prepareGuiRender();
                this->flipBuffer();
            }
            return;
        }

        if( !this->bDoRun )
        {
            tskl->kill();
            return;
        }

        if( this->initApi() )
            this->bIsRun = 1;
        else
            this->bDoRun = 0;
    }

    //init graphics api
    bool renderer::initApi( void )
    {
        std::cout << "renderer init\r\n";
        return 1;
    }

    //deinit graphics api
    void renderer::deinitApi( void )
    {
        std::cout << "renderer deinit\r\n";
    }

    //do background graphics api processing
    bool renderer::runApi( void )
    {
        std::cout << "r";
        return 1;
    }

};
