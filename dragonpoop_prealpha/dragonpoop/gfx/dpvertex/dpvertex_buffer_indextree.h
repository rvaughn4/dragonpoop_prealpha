
#ifndef dragonpoop_dpvertex_buffer_indextree_h
#define dragonpoop_dpvertex_buffer_indextree_h

#include "../../core/bytetree/dpid_bytetree.h"
#include <stdint.h>

namespace dragonpoop
{

    class dpvertex_buffer_indextree : public dpid_bytetree
    {
    private:

    protected:

    public:

        //ctor
        dpvertex_buffer_indextree( void );
        //dtor
        virtual ~dpvertex_buffer_indextree( void );
        //find leaf
        uint16_t findLeaf( dpid id );
        //add leaf
        void addLeaf( dpid id, uint16_t i );
        
    };
    
};

#endif