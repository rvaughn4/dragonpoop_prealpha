
#include "dpthread.h"
#include "dpthread_lock.h"
#include "../dpmutex/dpmutexes.h"
#include "../dptask/dptasks.h"
#include "../dptaskpool/dptaskpools.h"
#include "../shared_obj/shared_obj_guard.h"
#include <stdlib.h>
#include <string.h>

namespace dragonpoop
{

    //ctor
    dpthread::dpthread( dpmutex_master *ml, unsigned int id )
    {
        this->id = id;
        this->lm = ml;
        this->tp = 0;
        this->trun = 1;
        this->l = this->lm->genMutex();
        memset( &this->tasks, 0, sizeof( this->tasks ) );
        this->thd = new std::thread( dpthread_threadproc, this );
    }

    //ctor
    dpthread::dpthread( dpmutex_master *ml, unsigned int id, dptaskpool_ref *tp )
    {
        this->id = id;
        this->lm = ml;
        this->tp = tp;
        this->trun = 1;
        this->l = this->lm->genMutex();
        memset( &this->tasks, 0, sizeof( this->tasks ) );
        this->thd = new std::thread( dpthread_threadproc, this );
    }

    //dtor
    dpthread::~dpthread( void )
    {
        this->kill();
        delete this->thd;
        this->deleteTasks();
        this->lm->destroyMutex( &this->l );
    }

    //add new task (creates a ref)
    void dpthread::addTask( dptask_ref *t )
    {
        dptask_ref *at;
        dptask_writelock *tl;
        shared_obj_guard g;

        tl = (dptask_writelock *)g.writeLock( t );
        if( !tl )
            return;
        at = (dptask_ref *)tl->getRef();
        this->pushToRun( at );
    }

    //add new task (creates a ref)
    void dpthread::addTask( dptask *t )
    {
        dptask_ref *at;
        dptask_writelock *tl;
        shared_obj_guard g;

        tl = (dptask_writelock *)g.writeLock( t );
        if( !tl )
            return;
        at = (dptask_ref *)tl->getRef();
        this->pushToRun( at );
    }

    //add task pool
    void dpthread::addPool( dptaskpool *tp )
    {
        dptaskpool_writelock *tpl;
        shared_obj_guard g;

        if( this->tp )
            delete this->tp;
        this->tp = 0;

        tpl = (dptaskpool_writelock *)g.writeLock( tp );
        if( !tpl )
            return;
        this->tp = (dptaskpool_ref *)tpl->getRef();
    }

    //get tick count in ms
    uint64_t dpthread::getTicks( void )
    {
        return this->ticks;
    }

    //get epoch time in seconds
    uint64_t dpthread::getEpoch( void )
    {
        return this->epoch;
    }

    //lock
    dpthread_lock *dpthread::lock( void )
    {
        dpmutex_writelock *wl;

        wl = this->l->tryWriteLock( 30 );
        if( !wl )
            return 0;

        return new dpthread_lock( this, wl );
    }

    //add task to run
    void dpthread::pushToRun( dptask_ref *t )
    {
        unsigned int nc, nm, i;
        dptask_ref **nb;
        dpthread_tasklist *tl;

        tl = &this->tasks.torun;
        if( tl->buffer && tl->cnt < tl->max )
        {
            for( i = 0; i < tl->cnt; i++ )
            {
                if( !tl->buffer[ i ] )
                {
                    tl->buffer[ i ] = t;
                    return;
                }
            }
        }

        nc = tl->cnt + 1;
        if( !tl->buffer || tl->max <= nc )
        {
            nm = 3 + nc * 2;
            nb = (dptask_ref **)malloc( sizeof(dptask_ref *) * nm );
            if( !nb )
                return;
            memset( nb, 0, sizeof(dptask_ref *) * nm );
            if( tl->buffer )
            {
                memcpy( nb, tl->buffer, tl->cnt * sizeof(dptask_ref *) );
                free( tl->buffer );
            }
            tl->buffer = nb;
            tl->max = nm;
        }

        tl->buffer[ nc - 1 ] = t;
        tl->cnt++;
    }

    //get and remove task from to run
    dptask_ref *dpthread::popToRun( void )
    {
        unsigned int i;
        dptask_ref *t;
        dpthread_tasklist *tl;

        tl = &this->tasks.torun;
        if( !tl->buffer )
            return 0;

        for( i = 0; i < tl->cnt; i++ )
        {
            t = tl->buffer[ i ];
            if( t )
            {
                tl->buffer[ i ] = 0;
                return t;
            }
        }

        return 0;
    }

    //add task to beenran
    void dpthread::pushBeenRan( dptask_ref *t )
    {
        unsigned int nc, nm, i;
        dptask_ref **nb;
        dpthread_tasklist *tl;

        tl = &this->tasks.beenran;
        if( tl->buffer && tl->cnt < tl->max )
        {
            for( i = 0; i < tl->cnt; i++ )
            {
                if( !tl->buffer[ i ] )
                {
                    tl->buffer[ i ] = t;
                    return;
                }
            }
        }

        nc = tl->cnt + 1;
        if( !tl->buffer || tl->max <= nc )
        {
            nm = 3 + nc * 2;
            nb = (dptask_ref **)malloc( sizeof(dptask_ref *) * nm );
            if( !nb )
                return;
            memset( nb, 0, sizeof(dptask_ref *) * nm );
            if( tl->buffer )
            {
                memcpy( nb, tl->buffer, tl->cnt * sizeof(dptask_ref *) );
                free( tl->buffer );
            }
            tl->buffer = nb;
            tl->max = nm;
        }

        tl->buffer[ nc - 1 ] = t;
        tl->cnt++;
    }

    //get and remove task from beenran
    dptask_ref *dpthread::popBeenRan( void )
    {
        unsigned int i;
        dptask_ref *t;
        dpthread_tasklist *tl;

        tl = &this->tasks.beenran;
        if( !tl->buffer )
            return 0;

        for( i = 0; i < tl->cnt; i++ )
        {
            t = tl->buffer[ i ];
            if( t )
            {
                tl->buffer[ i ] = 0;
                return t;
            }
        }

        return 0;
    }

    //handle task pool
    void dpthread::handlePool( void )
    {
        dptask_ref *t;
        dptask_readlock *tl;
        dptaskpool_writelock *tpl;
        shared_obj_guard g, g0;

        this->tp_new_cnt++;
        if( this->tp_new_cnt < 20 )
            return;

        if( !this->tp )
            return;
        tpl = (dptaskpool_writelock *)g.tryWriteLock( this->tp, 3 );
        if( !tpl )
            return;

        t = tpl->p->popTask();
        this->pushToRun( t );

        if( this->ticks - this->tp_dump_cnt < 1000 )
            return;
        this->tp_dump_cnt = this->ticks;

        t = this->popBeenRan();
        while( t )
        {
            tl = (dptask_readlock *)g0.readLock( t );
            if( tl )
            {
                if( tl->isSingleThread() )
                    this->pushToRun( t );
                else
                    tpl->p->pushTask( t );
            }
            else
                tpl->p->pushTask( t );
            t = this->popBeenRan();
        }
    }

    //delete all tasks (or throw them on pool)
    void dpthread::deleteTasks( void )
    {
        unsigned int i, j;
        dptask_ref *t;
        dpthread_tasklist *tl;

        for( j = 0; j < 2; j++ )
        {
            if( j == 1 )
                tl = &this->tasks.beenran;
            else
                tl = &this->tasks.torun;

            if( !tl->buffer )
            {
                tl->cnt = tl->max = 0;
                continue;
            }

            for( i = 0; i < tl->cnt; i++ )
            {
                t = tl->buffer[ i ];
                delete t;
            }

            free( tl->buffer );
            tl->cnt = tl->max = 0;
        }

    }

    //return id
    unsigned int dpthread::getId( void )
    {
        return this->id;
    }

    //kill thread
    void dpthread::kill( void )
    {
        this->trun = 0;
        if( this->thd->joinable() )
            this->thd->join();
    }

    //generate unique dpid
    dpid dpthread::genId( void )
    {
        dpid r;
        union
        {
            void *p;
            uint64_t pi;
        };

        p = (void *)this;
        r.addr = (uint32_t)pi;
        this->idctr++;
        r.counter = this->idctr;
        r.epoch = (uint32_t)this->epoch;
        r.ticks = (uint32_t)this->ticks;
        r.randno = rand();

        return r;
    }

    //ran by thread
    void dpthread_threadproc( dpthread *t )
    {
        dpthread_lock *tl;
        dptask_ref *r;
        dptask_writelock *rl;
        shared_obj_guard g;

        while( t->trun )
        {
            tl = t->lock();
            if( !tl )
            {
                std::this_thread::sleep_for( std::chrono::milliseconds( 1 ) );
                continue;
            }
            t->handlePool();

            t->epoch = std::chrono::seconds( std::chrono::seconds( std::time( 0 ) ) ).count();
            t->ticks = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now().time_since_epoch()).count();

            r = t->popToRun();
            if( !r )
            {
                r = t->popBeenRan();
                while( r )
                {
                    t->pushToRun( r );
                    r = t->popBeenRan();
                }
                delete tl;
                std::this_thread::sleep_for( std::chrono::milliseconds( 10 ) );
                continue;
            }

            if( !r->isLinked() )
            {
                delete r;
                delete tl;
                continue;
            }

            rl = (dptask_writelock *)g.tryWriteLock( r, 3 );
            if( !rl )
            {
                t->pushBeenRan( r );
                delete tl;
                g.unlock();
                std::this_thread::sleep_for( std::chrono::milliseconds( 1 ) );
                continue;
            }

            if( rl->getLastTime() + rl->getDelay() > t->ticks )
            {
                t->pushBeenRan( r );
                delete tl;
                g.unlock();
                std::this_thread::sleep_for( std::chrono::milliseconds( 1 ) );
                continue;
            }

            if( !rl->isAlive() )
            {
                delete tl;
                g.unlock();
                delete r;
                std::this_thread::sleep_for( std::chrono::milliseconds( 1 ) );
                continue;
            }

            rl->run( rl, tl );
            rl->setLastTime( t->ticks );
            t->pushBeenRan( r );
            g.unlock();

            delete tl;
            std::this_thread::sleep_for( std::chrono::milliseconds( 1 ) );
        }
    }

};
