
#include "dpvertex_buffer_indextree.h"

namespace dragonpoop
{

    //ctor
    dpvertex_buffer_indextree::dpvertex_buffer_indextree( void )
    {

    }

    //dtor
    dpvertex_buffer_indextree::~dpvertex_buffer_indextree( void )
    {
        this->clear();
    }

    //find leaf
    uint16_t dpvertex_buffer_indextree::findLeaf( dpid id )
    {
        union
        {
            uint64_t r;
            void *rp;
        };
        rp = this->dpid_bytetree::findLeaf( id );
        return (uint16_t)r;
    }

    //add leaf
    void dpvertex_buffer_indextree::addLeaf( dpid id, uint16_t i )
    {
        union
        {
            uint64_t r;
            void *rp;
        };
        r = i;
        this->dpid_bytetree::addLeaf( id, rp );
    }

};
