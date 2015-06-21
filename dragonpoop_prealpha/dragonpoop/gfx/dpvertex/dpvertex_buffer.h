
#ifndef dragonpoop_dpvertex_buffer_h
#define dragonpoop_dpvertex_buffer_h

#include "dpvertex.h"

namespace dragonpoop
{

    class dpvertex_buffer_indextree;

    class dpvertex_buffer
    {

    private:

        struct
        {
            dpvertex *ptr;
            unsigned int cnt, max;
        } buffer;
        dpvertex_buffer_indextree *t;

    protected:

    public:

        //ctor
        dpvertex_buffer( void );
        //dtor
        virtual ~dpvertex_buffer( void );
        //copy
        void copy( dpvertex_buffer *c );
        //get size
        unsigned int getSize( void );
        //get buffer
        dpvertex *getBuffer( void );
        //add vertex
        void addVertex( dpvertex *v );
        //clear
        void clear( void );
        //find vertex offset using vertex id
        uint16_t findVertex( dpid id );
        
    };
    
};

#endif