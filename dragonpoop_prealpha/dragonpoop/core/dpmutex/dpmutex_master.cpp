
#include "../dpspinlock/dpsponlock.h"
#include "dpmutex_master.h"
#include "dpmutex.h"
#include "dpmutex_lock.h"
#include "dpmutex_writelock.h"
#include "dpmutex_readlock.h"
#include <ctime>
#include <ratio>
#include <chrono>
#include <thread>

namespace dragonpoop
{

    //ctor
    dpmutex_master::dpmutex_master( void )
    {
        this->slk = new dpspinlock();
    }

    //dtor
    dpmutex_master::~dpmutex_master( void )
    {
        delete this->slk;
    }

    //generate new mutex
    dpmutex *dpmutex_master::genMutex( void )
    {
        dpmutex *r;

        this->slk->lock();

        r = new dpmutex( this );

        this->slk->unlock();

        return r;
    }

    //destroy mutex
    void dpmutex_master::destroyMutex( dpmutex **mm )
    {
        std::atomic<int> *wc, *rc;
        dpmutex *m;

        if( !mm )
            return;
        m = *mm;
        if( !m )
            return;
        *mm = 0;

        this->slk->lock();

        wc = m->getWriteCounter();
        rc = m->getReadCounter();

        if( *wc + *rc == 0 )
            delete m;
        //else{ abort!!!! }

        this->slk->unlock();
    }

    //attempt to generate read lock on mutex
    dpmutex_readlock *dpmutex_master::genReadLock( dpmutex *m, uint64_t wait_ms )
    {
        dpmutex_readlock *r;
        std::atomic<int> *wc, *rc;
        std::thread::id i = std::this_thread::get_id();

        r = 0;
        this->slk->lock();

        wc = m->getWriteCounter();
        rc = m->getReadCounter();

        if( *wc <= 0 || m->tid == i )
        {
            *rc = *rc + 1;
            if( *rc == 1 )
                m->rtid = i;
            else
                memset( &m->rtid, 0, sizeof( m->rtid ) );
            r = new dpmutex_readlock( m );
        }

        this->slk->unlock();
        
        return r;
    }

    //atempt to generate write lock on mutex
    dpmutex_writelock *dpmutex_master::genWriteLock( dpmutex *m, uint64_t wait_ms )
    {
        dpmutex_writelock *r;
        std::atomic<int> *wc, *rc;
        std::thread::id i = std::this_thread::get_id();

        r = 0;
        this->slk->lock();

        wc = m->getWriteCounter();
        rc = m->getReadCounter();

        if( *rc > 1 || ( *rc > 0 && m->rtid != i ) )
        {
            this->slk->unlock();
            return 0;
        }

        if( *wc <= 0 || i == m->tid )
        {
            *wc = *wc + 1;
            m->tid = i;
            r = new dpmutex_writelock( m );
        }

        this->slk->unlock();
        
        return r;
    }

    //destroy lock
    void dpmutex_master::destroyLock( dpmutex_lock **ll )
    {
        dpmutex *m;
        std::atomic<int> *wc, *rc;
        dpmutex_lock *l;

        if( !ll )
            return;
        l = *ll;
        if( !l )
            return;
        *ll = 0;

        this->slk->lock();

        m = l->getMutex();
        wc = m->getWriteCounter();
        rc = m->getReadCounter();

        if( *rc > 0 )
            *rc = *rc - 1;
        if( *wc > 0 )
            *wc = *wc - 1;
        memset( &m->rtid, 0, sizeof(m->rtid) );
        delete l;

        this->slk->unlock();
    }

    //write lock with wait time/timeout in ms
    dpmutex_writelock *dpmutex_master::writeLock( dpmutex *m, uint64_t t )
    {
        dpmutex_writelock *l;

        l = this->genWriteLock( m, t );
        if( l )
            return l;
        while( t )
        {
            std::this_thread::sleep_for( std::chrono::milliseconds( 1 ) );
            t--;
            l = this->genWriteLock( m, t );
            if( l )
                return l;
        }

        return 0;
    }

    //read lock with timeout in ms
    dpmutex_readlock *dpmutex_master::readLock( dpmutex *m, uint64_t t )
    {
        dpmutex_readlock *l;

        l = this->genReadLock( m, t );
        if( l )
            return l;
        while( t )
        {
            std::this_thread::sleep_for( std::chrono::milliseconds( 1 ) );
            t--;
            l = this->genReadLock( m, t );
            if( l )
                return l;
        }

        return 0;
    }

    //does not return until write locked
    dpmutex_writelock *dpmutex_master::writeLock( dpmutex *m )
    {
        dpmutex_writelock *l;

        do
        {
            l = this->genWriteLock( m, 100 );
            if( l )
                return l;
        }
        while( !l );

        return 0;
    }

    //does not return until read locked
    dpmutex_readlock *dpmutex_master::readLock( dpmutex *m )
    {
        dpmutex_readlock *l;

        do
        {
            l = this->genReadLock( m, 100 );
            if( l )
                return l;
        }
        while( !l );

        return 0;
    }

};
