
#ifndef dragonpoop_model_vertex_readlock_h
#define dragonpoop_model_vertex_readlock_h

#include "../model_component/model_component_readlock.h"
#include "../../dpvertex/dpxyzw.h"
#include "../../dpvertex/dpxyzw_f.h"
#include "../../dpvertex/dpxyz_f.h"

namespace dragonpoop
{
    class model_vertex;

    class model_vertex_readlock : public model_component_readlock
    {

    private:

        model_vertex *t;

    protected:

        //ctor
        model_vertex_readlock( model_vertex *t, dpmutex_readlock *l );
        //dtor
        virtual ~model_vertex_readlock( void );

    public:

        //get position
        void getPosition( dpxyzw *p );
        //get position
        void getPosition( dpxyzw_f *p );
        //get position
        void getPosition( dpxyz_f *p );

        friend class model_vertex;
    };
    
};

#endif