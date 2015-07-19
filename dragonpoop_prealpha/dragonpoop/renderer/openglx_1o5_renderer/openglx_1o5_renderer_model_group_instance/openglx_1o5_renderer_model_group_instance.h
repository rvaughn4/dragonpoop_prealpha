
#ifndef dragonpoop_openglx_1o5_renderer_model_group_instance_h
#define dragonpoop_openglx_1o5_renderer_model_group_instance_h

#include "../../renderer_model_group_instance/renderer_model_group_instance.h"
#include "../../../gfx/dpbitmap/dpbitmap.h"

namespace dragonpoop
{

    class openglx_1o5_renderer_ref;
    class openglx_1o5_renderer_writelock;
    class openglx_1o5_renderer_model_group_instance_writelock;
    class openglx_1o5_renderer_model_group_instance_readlock;
    class openglx_1o5_renderer_model_group_instance_ref;
    class model_material_readlock;

    typedef renderer_model_instance_writelock openglx_1o5_renderer_model_instance_writelock;

    class openglx_1o5_renderer_model_group_instance : public renderer_model_group_instance
    {

    private:

        openglx_1o5_renderer_ref *r;
        unsigned int tex_diffuse, tex_alpha;
        bool bTexLoaded;

        //create texture based on bitmap
        void makeGlTex( unsigned int *p_tex, dpbitmap *bm );
        //release texture
        void killGltex( unsigned int *p_tex );

    protected:

        //generate read lock
        virtual shared_obj_readlock *genReadLock( shared_obj *p, dpmutex_readlock *l );
        //generate write lock
        virtual shared_obj_writelock *genWriteLock( shared_obj *p, dpmutex_writelock *l );
        //generate ref
        virtual shared_obj_ref *genRef( shared_obj *p, std::shared_ptr<shared_obj_refkernal> *k );
        //called after run
        virtual void onRun( dpthread_lock *thd, renderer_model_instance_writelock *m, renderer_model_group_instance_writelock *grp, renderer_writelock *r );
        //called after sync
        virtual void onSync( dpthread_lock *thd, renderer_model_instance_writelock *m, renderer_model_group_instance_writelock *grp, renderer_writelock *r, model_material_readlock *mat );
        //return diffuse texture
        unsigned int getDiffuseTex( void );
        //return alpha texture
        unsigned int getAlphaTex( void );

    public:

        //ctor
        openglx_1o5_renderer_model_group_instance( gfx_writelock *g, openglx_1o5_renderer_writelock *r, model_instance_writelock *m, model_group_instance_writelock *grp );
        //dtor
        virtual ~openglx_1o5_renderer_model_group_instance( void );

        friend class openglx_1o5_renderer_model_group_instance_readlock;
        friend class openglx_1o5_renderer_model_group_instance_writelock;
    };
    
};

#endif