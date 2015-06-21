
#include "dpsponlock.h"
#include <thread>

namespace dragonpoop
{

    //ctor
    dpspinlock::dpspinlock( void )
    {
        this->unlock();
    }

    //dtor
    dpspinlock::~dpspinlock( void )
    {
    }

    //locks
    void dpspinlock::lock( void )
    {
        while( this->f.test_and_set( std::memory_order_acquire ) );
    }

    //unlocks
    void dpspinlock::unlock( void )
    {
        this->f.clear( std::memory_order_release );
    }

};
