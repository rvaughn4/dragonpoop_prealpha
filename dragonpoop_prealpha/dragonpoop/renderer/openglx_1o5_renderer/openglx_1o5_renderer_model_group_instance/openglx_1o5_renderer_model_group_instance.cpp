
#include "openglx_1o5_renderer_model_group_instance.h"
#include "openglx_1o5_renderer_model_group_instance_writelock.h"
#include "openglx_1o5_renderer_model_group_instance_readlock.h"
#include "openglx_1o5_renderer_model_group_instance_ref.h"
#include "../openglx_1o5_renderer_writelock.h"
#include "../openglx_1o5_renderer_ref.h"
#include "../openglx_1o5_renderer.h"
#include "../../../gfx/model/model_material/model_material_readlock.h"

namespace dragonpoop
{

    //ctor
    openglx_1o5_renderer_model_group_instance::openglx_1o5_renderer_model_group_instance( gfx_writelock *g, openglx_1o5_renderer_writelock *r, model_instance_writelock *m, model_group_instance_writelock *grp ) : renderer_model_group_instance( g, r, m, grp )
    {
        this->r = (openglx_1o5_renderer_ref *)r->getRef();
        this->bTexLoaded = 0;
        this->tex_diffuse = this->tex_alpha = 0;
    }

    //dtor
    openglx_1o5_renderer_model_group_instance::~openglx_1o5_renderer_model_group_instance( void )
    {
        delete this->r;
    }

    //generate read lock
    shared_obj_readlock *openglx_1o5_renderer_model_group_instance::genReadLock( shared_obj *p, dpmutex_readlock *l )
    {
        return new openglx_1o5_renderer_model_group_instance_readlock( (openglx_1o5_renderer_model_group_instance *)p, l );
    }

    //generate write lock
    shared_obj_writelock *openglx_1o5_renderer_model_group_instance::genWriteLock( shared_obj *p, dpmutex_writelock *l )
    {
        return new openglx_1o5_renderer_model_group_instance_writelock( (openglx_1o5_renderer_model_group_instance *)p, l );
    }

    //generate ref
    shared_obj_ref *openglx_1o5_renderer_model_group_instance::genRef( shared_obj *p, std::shared_ptr<shared_obj_refkernal> *k )
    {
        return new openglx_1o5_renderer_model_group_instance_ref( (openglx_1o5_renderer_model_group_instance *)p, k );
    }

    //called after run
    void openglx_1o5_renderer_model_group_instance::onRun( dpthread_lock *thd, renderer_model_instance_writelock *m, renderer_model_group_instance_writelock *grp, renderer_writelock *r )
    {

    }

    //called after sync
    void openglx_1o5_renderer_model_group_instance::onSync( dpthread_lock *thd, renderer_model_instance_writelock *m, renderer_model_group_instance_writelock *grp, renderer_writelock *r, model_material_readlock *mat )
    {
        dpbitmap *b;

        if( this->bTexLoaded )
            return;
        this->bTexLoaded = 1;

        this->killGltex( &this->tex_diffuse );
        this->killGltex( &this->tex_alpha );

        b = new dpbitmap();

        if( mat->getDiffuseTexture( b ) )
            this->makeGlTex( &this->tex_diffuse, b );
        if( mat->getAlphaMapTexture( b ) )
            this->makeGlTex( &this->tex_alpha, b );
        delete b;
    }

    //create texture based on bitmap
    void openglx_1o5_renderer_model_group_instance::makeGlTex( unsigned int *p_tex, dpbitmap *img )
    {
        unsigned int sz, bits, w, h, d, l, m;
        char *buffer;
        bool doMip, doLin;
        dpbitmap ci;

        this->killGltex( p_tex );

        sz = img->getSize();
        w = img->getWidth();
        h = img->getHeight();
        bits = img->getBitsPerPixel();
        buffer = img->getBuffer();

        if( !p_tex || !buffer || !sz || !w || !h || ( bits != 24 && bits != 32 ) )
            return;

        doMip = 1;
        doLin = 1;

        glGenTextures( 1, p_tex );
        if( !*p_tex )
            return;

        glBindTexture( GL_TEXTURE_2D, *p_tex );

        if( doLin )
        {
            glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
            if( doMip )
                glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR );
            else
                glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
        }
        else
        {
            glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
            if( doMip )
                glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST );
            else
                glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
        }

        l = w;
        if( h > l )
            l = h;
        if( l > 512 )
            l = 512;
        d = 8;
        while( d < l )
            d *= 8;

        if( doMip )
        {

            m = 0;
            l = d * 2;
            do
            {
                l = l / 2;
                m++;
            }
            while( l > 1 );
            m--;
            glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, 0 );
            glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, m );

            d *= 2;
            l = 0;
            do
            {
                d /= 2;

                ci.reset();
                if( !ci.resize( d, d ) )
                    d = 0;
                else
                {
                    ci.blit( img, 0 );
                    buffer = ci.getBuffer();
                    glTexImage2D( GL_TEXTURE_2D, l, GL_RGBA8, d, d, 0, GL_RGBA, GL_UNSIGNED_BYTE, buffer );
                    l++;
                }
            }
            while( d > 1 );
        }
        else
        {
            glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, 0 );
            glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 0 );

            ci.reset();
            if( !ci.resize( d, d ) )
                d = 0;
            else
            {

                ci.blit( img, 0 );
                buffer = ci.getBuffer();
                glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA8, d, d, 0, GL_RGBA, GL_UNSIGNED_BYTE, buffer );
            }
        }
    }

    //release texture
    void openglx_1o5_renderer_model_group_instance::killGltex( unsigned int *p_tex )
    {
        if( !p_tex || !*p_tex )
            return;
        glDeleteTextures( 1, p_tex );
        *p_tex = 0;
    }

    //return diffuse texture
    unsigned int openglx_1o5_renderer_model_group_instance::getDiffuseTex( void )
    {
        return this->tex_diffuse;
    }

    //return alpha texture
    unsigned int openglx_1o5_renderer_model_group_instance::getAlphaTex( void )
    {
        return this->tex_alpha;
    }

};
