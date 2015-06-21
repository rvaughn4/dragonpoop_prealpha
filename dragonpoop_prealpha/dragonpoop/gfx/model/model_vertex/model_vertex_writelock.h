
#ifndef dragonpoop_model_vertex_writelock_h
#define dragonpoop_model_vertex_writelock_h

#include "../model_component/model_component_writelock.h"
#include "../../dpvertex/dpxyzw.h"
#include "../../dpvertex/dpxyzw_f.h"
#include "../../dpvertex/dpxyz_f.h"

namespace dragonpoop
{
    class model_vertex;

    class model_vertex_writelock : public model_component_writelock
    {

    private:

        model_vertex *t;

    protected:

        //ctor
        model_vertex_writelock( model_vertex *t, dpmutex_writelock *l );
        //dtor
        virtual ~model_vertex_writelock( void );

    public:

        //get position
        void getPosition( dpxyzw *p );
        //get position
        void getPosition( dpxyzw_f *p );
        //get position
        void getPosition( dpxyz_f *p );
        //get position
        void setPosition( dpxyzw *p );
        //get position
        void setPosition( dpxyzw_f *p );
        //get position
        void setPosition( dpxyz_f *p );

        friend class model_vertex;
    };
    
};

#endif