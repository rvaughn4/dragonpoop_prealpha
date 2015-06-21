
#ifndef dragonpoop_model_triangle_vertex_writelock_h
#define dragonpoop_model_triangle_vertex_writelock_h

#include "../model_component/model_component_writelock.h"
#include "../../dpvertex/dpvertexes.h"

namespace dragonpoop
{
    class model_triangle_vertex;
    class model_triangle_vertex_ref;
    class model_triangle_ref;
    class model_vertex_ref;

    class model_triangle_vertex_writelock : public model_component_writelock
    {

    private:

        model_triangle_vertex *t;

    protected:

        //ctor
        model_triangle_vertex_writelock( model_triangle_vertex *t, dpmutex_writelock *l );
        //dtor
        virtual ~model_triangle_vertex_writelock( void );

    public:

        //get triangle id
        dpid getTriangleId( void );
        //get triangle
        model_triangle_ref *getTriangle( void );
        //get vertex id
        dpid getVertexId( void );
        //get vertex
        model_vertex_ref *getVertex( void );
        //set normal
        void setNormal( dpxyzw *p );
        //set normal
        void setNormal( dpxyzw_f *p );
        //set normal
        void setNormal( dpxyz_f *p );
        //get normal
        void getNormal( dpxyzw *p );
        //get normal
        void getNormal( dpxyzw_f *p );
        //get normal
        void getNormal( dpxyz_f *p );
        //set texcoord
        void setTexcoord( uint8_t index, dpst *p );
        //set texcoord
        void setTexcoord( uint8_t index, dpst_f *p );
        //get texcoord
        void getTexcoord( uint8_t index, dpst *p );
        //get texcoord
        void getTexcoord( uint8_t index, dpst_f *p );

        friend class model_triangle_vertex;
    };
    
};

#endif