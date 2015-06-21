
#ifndef dragonpoop_dpmutex_h
#define dragonpoop_dpmutex_h

#include <stdint.h>
#include <atomic>
#include <thread>

namespace dragonpoop
{

    class dpmutex_master;
    class dpmutex_readlock;
    class dpmutex_writelock;

    class dpmutex
    {

    private:

        std::atomic<int> ireadlock, iwritelock;
        dpmutex_master *m;
        std::atomic<std::thread::id> tid;

    protected:

        //ctor
        dpmutex( dpmutex_master *m );
        //dtor
        virtual ~dpmutex( void );
        //returns pointer to read lock counter
        std::atomic<int> *getReadCounter( void );
        //returns pointer to write lock counter
        std::atomic<int> *getWriteCounter( void );

    public:

        //try read lock
        dpmutex_readlock *tryReadLock( void );
        //try write lock
        dpmutex_writelock *tryWriteLock( void );
        //try read lock until timeout in ms
        dpmutex_readlock *tryReadLock( uint64_t w );
        //try write lock until timeout in ms
        dpmutex_writelock *tryWriteLock( uint64_t w );
        //do not return until read locked
        dpmutex_readlock *readLock( void );
        //do not return until write locked
        dpmutex_writelock *writeLock( void );

        friend class dpmutex_master;
        friend class dpmutex_lock;
    };
    
};

#endif