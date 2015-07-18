
#include "dragonpoop/dragonpoop.h"

namespace dragonpoop
{
    class aaa : public dptask_owner
    {
    public:

        gfx_ref *g;

        aaa( void )
        {

        }

        virtual ~aaa( void )
        {
        }

        //run by task
        virtual void run( dptask_writelock *tl, dpthread_lock *th )
        {
            model_ref *mr;
            model_writelock *ml;
            shared_obj_guard g;
            gfx_writelock *gl;
            model_instance_ref *mi;

            gl = (gfx_writelock *)g.writeLock( this->g );
            mr = gl->createModel( th );
            g.unlock();

            ml = (model_writelock *)g.writeLock( mr );

            ms3d_model_loader::load( th, ml, "felhound.ms3d" );
            ms3d_model_loader::save( th, ml, "o1.ms3d" );
            mi = ml->createInstance( th );

            //ml->clear();
         //   ms3d_model_loader::load( th, ml, "o1.ms3d" );
         //   ms3d_model_loader::save( th, ml, "o2.ms3d" );

          //  ml->kill();
            tl->kill();
            delete mr;
            delete mi;
        }

    };
}

int main(int argc, const char * argv[])
{
    dragonpoop::core *c = new dragonpoop::core();
    dragonpoop::aaa a;
    dragonpoop::dptask *t;

    a.g = c->getGfx();
    t = new dragonpoop::dptask( c->getMutexMaster(), &a, 10000, 0 );
    c->addTask( t );

    while( c->isRunning() )
        std::this_thread::sleep_for( std::chrono::milliseconds( 500 ) );

    delete t;
    delete a.g;
    delete c;

    return 0;
}
