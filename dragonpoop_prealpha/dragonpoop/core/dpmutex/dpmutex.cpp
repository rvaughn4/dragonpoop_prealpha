
#include "dpmutex.h"
#include "dpmutex_master.h"
#include "../dpspinlock/dpsponlock.h"

namespace dragonpoop
{

    //ctor
    dpmutex::dpmutex( dpmutex_master *m )
    {
        this->m = m;
        this->ireadlock = 0;
        this->iwritelock = 0;
    }

    //dtor
    dpmutex::~dpmutex( void )
    {
    }

    //returns pointer to read lock counter
    std::atomic<int> *dpmutex::getReadCounter( void )
    {
        return &this->ireadlock;
    }

    //returns pointer to write lock counter
    std::atomic<int> *dpmutex::getWriteCounter( void )
    {
        return &this->iwritelock;
    }

    //try read lock
    dpmutex_readlock *dpmutex::tryReadLock( void )
    {
        return this->m->genReadLock( this, 1 );
    }

    //try write lock
    dpmutex_writelock *dpmutex::tryWriteLock( void )
    {
        return this->m->genWriteLock( this, 1 );
    }

    //try read lock until timeout in ms
    dpmutex_readlock *dpmutex::tryReadLock( uint64_t w )
    {
        return this->m->readLock( this, w );
    }

    //try write lock until timeout in ms
    dpmutex_writelock *dpmutex::tryWriteLock( uint64_t w )
    {
        return this->m->writeLock( this, w );
    }

    //do not return until read locked
    dpmutex_readlock *dpmutex::readLock( void )
    {
        return this->m->readLock( this );
    }

    //do not return until write locked
    dpmutex_writelock *dpmutex::writeLock( void )
    {
        return this->m->writeLock( this );
    }

};
