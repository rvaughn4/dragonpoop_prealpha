
#ifndef dragonpoop_renderer_h
#define dragonpoop_renderer_h

#include "../core/shared_obj/shared_obj.h"

namespace dragonpoop
{

    class dptaskpool_writelock;
    class dptask;
    class renderer_task;
    class dpthread_lock;
    class dptask_writelock;
    class core;
    class gfx_writelock;
    class model_instance_writelock;
    class renderer_writelock;
    class renderer_model_instance;
    class renderer_model_group_instance;
    class model_group_instance_writelock;

    class renderer : public shared_obj
    {

    private:

        dptask *tsk;
        renderer_task *gtsk;
        core *c;
        std::atomic<bool> bDoRun, bIsRun;
        std::list<renderer_model_instance *> models;
        uint64_t lastMakeModel;

    protected:

        //generate read lock
        virtual shared_obj_readlock *genReadLock( shared_obj *p, dpmutex_readlock *l );
        //generate write lock
        virtual shared_obj_writelock *genWriteLock( shared_obj *p, dpmutex_writelock *l );
        //generate ref
        virtual shared_obj_ref *genRef( shared_obj *p, std::shared_ptr<shared_obj_refkernal> *k );
        //stop renderer task
        void kill( void );
        //run renderer from task
        void run( dptask_writelock *tskl, dpthread_lock *thd, renderer_writelock *r );
        //init graphics api
        virtual bool initApi( void );
        //deinit graphics api
        virtual void deinitApi( void );
        //do background graphics api processing
        virtual bool runApi( void );
        //stop task and deinit api
        void _kill( void );
        //return screen/window width
        virtual unsigned int getWidth( void ) = 0;
        //return screen/window height
        virtual unsigned int getHeight( void ) = 0;
        //set viewport size
        virtual void setViewport( unsigned int w, unsigned int h ) = 0;
        //clear screen with color
        virtual void clearScreen( float r, float g, float b ) = 0;
        //prepare for rendering world
        virtual void prepareWorldRender( void ) = 0;
        //prepare for rendering gui
        virtual void prepareGuiRender( void ) = 0;
        //flip backbuffer and present scene to screen
        virtual void flipBuffer( void ) = 0;
        //generate model instance
        virtual renderer_model_instance *genModel( gfx_writelock *g, renderer_writelock *r, model_instance_writelock *m );
        //generate model group instance
        virtual renderer_model_group_instance *genGroup( gfx_writelock *g, renderer_writelock *r, model_instance_writelock *m, model_group_instance_writelock *grp );
        //make model instances
        void makeModels( gfx_writelock *g, renderer_writelock *r );
        //kill model instances
        void killModels( void );
        //run model instances
        void runModels( dpthread_lock *thd, renderer_writelock *r );
        //render model instances
        void renderModels( dpthread_lock *thd, renderer_writelock *r );

    public:

        //ctor
        renderer( core *c, dptaskpool_writelock *tp );
        //dtor
        virtual ~renderer( void );
        //returns true if running
        bool isRunning( void );
        //return core
        core *getCore( void );

        friend class renderer_readlock;
        friend class renderer_writelock;
    };
    
};

#endif