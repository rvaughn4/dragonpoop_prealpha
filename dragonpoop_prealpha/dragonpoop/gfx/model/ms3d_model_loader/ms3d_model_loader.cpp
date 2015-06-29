
#include "ms3d_model_loader.h"
#include "../model_vertex/model_vertexes.h"
#include "../model_group/model_groups.h"
#include "../model_triangle/model_triangles.h"
#include "../model_triangle_vertex/model_triangle_vertexes.h"
#include "../../../core/shared_obj/shared_obj_guard.h"

namespace dragonpoop
{

    //ctor
    ms3d_model_loader::ms3d_model_loader( model_writelock *ml, dpthread_lock *thd )
    {
        this->m = ml;
        this->thd = thd;
        this->anim.fps = 30;
        this->anim.current_time = 0;
        this->anim.cnt_frames = 0;
    }

    //dtor
    ms3d_model_loader::~ms3d_model_loader( void )
    {

    }

    //load file
    bool ms3d_model_loader::load( dpthread_lock *thd, model_writelock *ml, const char *fname )
    {
        ms3d_model_loader l( ml, thd );
        std::fstream f;

        f.open( fname, f.binary | f.in );
        if( !f.is_open() )
            return 0;
        if( !l.readHeader( &f ) )
            return 0;
        if( !l.readVertexSection( &f ) )
            return 0;
        if( !l.readTriangleSection( &f ) )
            return 0;
        if( !l.readGroupSection( &f ) )
            return 0;
        if( !l.readMaterialSection( &f ) )
            return 0;
        if( !l.readAnimationSection( &f ) )
            return 0;
        if( !l.readJointSection( &f ) )
            return 0;

        l.readCommentSection( &f );

        l.createVertexes();
        l.createGroups();
        l.createTriangles();

        return 1;
    }

    //save file
    bool ms3d_model_loader::save( dpthread_lock *thd, model_writelock *ml, const char *fname )
    {
        ms3d_model_loader l( ml, thd );
        std::fstream f;

        f.open( fname, f.binary | f.out | f.trunc );
        if( !f.is_open() )
            return 0;

        l.convertVertexes();
        l.convertGroups();
        l.convertTriangles();
        l.convertGroupTriangles();

        if( !l.writeHeader( &f ) )
            return 0;
        if( !l.writeVertexSection( &f ) )
            return 0;
        if( !l.writeTriangleSection( &f ) )
            return 0;
        if( !l.writeGroupSection( &f ) )
            return 0;
        if( !l.writeMaterialSection( &f ) )
            return 0;
        if( !l.writeAnimationSection( &f ) )
            return 0;
        if( !l.writeJointSection( &f ) )
            return 0;

        l.writeCommentSection( &f );


        return 1;
    }

    //load file header
    bool ms3d_model_loader::readHeader( std::fstream *f )
    {
        ms3d_model_header h;
        std::string s;

        f->read( (char *)&h, sizeof( h ) );

        if( h.version != 4 )
            return 0;
        h.version = 0;
        s.assign( (const char *)h.ms3d_magic );
        if( s.compare( ms3d_magic_number ) != 0 )
            return 0;

        return 1;
    }

    //save file header
    bool ms3d_model_loader::writeHeader( std::fstream *f )
    {
        ms3d_model_header h;
        std::string s;

        s.assign( ms3d_magic_number );
        s.copy( h.ms3d_magic, sizeof( h.ms3d_magic ) );
        h.version = 4;

        f->write( (char *)&h, sizeof( h ) );
        return 1;
    }

    //load vertex section
    bool ms3d_model_loader::readVertexSection( std::fstream *f )
    {
        ms3d_model_vertex_section h;
        uint16_t i;

        f->read( (char *)&h, sizeof( h ) );
        this->verts.clear();

        for( i = 0; i < h.cnt; i++ )
            this->readVertex( f );

        return 1;
    }

    //save vertex section
    bool ms3d_model_loader::writeVertexSection( std::fstream *f )
    {
        ms3d_model_vertex_section h;
        uint16_t i;

        h.cnt = (uint16_t)this->verts.size();
        f->write( (char *)&h, sizeof( h ) );

        for( i = 0; i < h.cnt; i++ )
            this->writeVertex( f, &this->verts[ i ] );

        return 1;
    }

    //load vertex
    bool ms3d_model_loader::readVertex( std::fstream *f )
    {
        ms3d_model_vertex_m h;

        memset( &h, 0, sizeof( h ) );
        f->read( (char *)&h.f, sizeof( h.f ) );
        this->verts.push_back( h );

        return 1;
    }

    //save vertex
    bool ms3d_model_loader::writeVertex( std::fstream *f, ms3d_model_vertex_m *h )
    {
        f->write( (char *)&h->f, sizeof( h->f ) );
        return 1;
    }

    //load triangle section
    bool ms3d_model_loader::readTriangleSection( std::fstream *f )
    {
        ms3d_model_triangle_section h;
        uint16_t i;

        f->read( (char *)&h, sizeof( h ) );
        this->tris.clear();

        for( i = 0; i < h.cnt; i++ )
            this->readTriangle( f );

        return 1;
    }

    //save triangle section
    bool ms3d_model_loader::writeTriangleSection( std::fstream *f )
    {
        ms3d_model_triangle_section h;
        uint16_t i;

        h.cnt = (uint16_t)this->tris.size();
        f->write( (char *)&h, sizeof( h ) );

        for( i = 0; i < h.cnt; i++ )
            this->writeTriangle( f, &this->tris[ i ] );

        return 1;
    }

    //load triangle
    bool ms3d_model_loader::readTriangle( std::fstream *f )
    {
        ms3d_model_triangle_m h;

        memset( &h, 0, sizeof( h ) );
        f->read( (char *)&h.f, sizeof( h.f ) );
        this->tris.push_back( h );

        return 1;
    }

    //save triangle
    bool ms3d_model_loader::writeTriangle( std::fstream *f, ms3d_model_triangle_m *h )
    {
        f->write( (char *)&h->f, sizeof( h->f ) );
        return 1;
    }

    //load group section
    bool ms3d_model_loader::readGroupSection( std::fstream *f )
    {
        ms3d_model_group_section h;
        uint16_t i;

        f->read( (char *)&h, sizeof( h ) );
        this->groups.clear();

        for( i = 0; i < h.cnt; i++ )
            this->readGroup( f );

        return 1;
    }

    //save group section
    bool ms3d_model_loader::writeGroupSection( std::fstream *f )
    {
        ms3d_model_group_section h;
        uint16_t i;

        h.cnt = (uint16_t)this->groups.size();
        f->write( (char *)&h, sizeof( h ) );

        for( i = 0; i < h.cnt; i++ )
            this->writeGroup( f, &this->groups[ i ] );

        return 1;
    }

    //load group
    bool ms3d_model_loader::readGroup( std::fstream *f )
    {
        ms3d_model_group_m h;
        uint16_t i;

        memset( &h, 0, sizeof( h ) );
        f->read( (char *)&h.f, sizeof( h.f ) );

        for( i = 0; i < h.f.cntTriangles; i++ )
            this->readGroupTriangle( f, &h );

        f->read( (char *)&h.e, sizeof( h.e ) );
        this->groups.push_back( h );

        return 1;
    }

    //save group
    bool ms3d_model_loader::writeGroup( std::fstream *f, ms3d_model_group_m *h )
    {
        uint16_t i;

        h->f.cntTriangles = (unsigned int)h->triangles.size();
        f->write( (char *)&h->f, sizeof( h->f ) );

        for( i = 0; i < h->f.cntTriangles; i++ )
            this->writeGroupTriangle( f, &h->triangles[ i ] );

        f->write( (char *)&h->e, sizeof( h->e ) );

        return 1;
    }

    //load group triangle
    bool ms3d_model_loader::readGroupTriangle( std::fstream *f, ms3d_model_group_m *h )
    {
        ms3d_model_group_triangle t;

        f->read( (char *)&t, sizeof( t ) );
        h->triangles.push_back( t );

        return 1;
    }

    //save group triangle
    bool ms3d_model_loader::writeGroupTriangle( std::fstream *f, ms3d_model_group_triangle *h )
    {
        f->write( (char *)h, sizeof(ms3d_model_group_triangle) );
        return 1;
    }

    //load materials
    bool ms3d_model_loader::readMaterialSection( std::fstream *f )
    {
        ms3d_model_material_section h;
        uint16_t i;

        f->read( (char *)&h, sizeof( h ) );
        this->mats.clear();

        for( i = 0; i < h.cnt; i++ )
            this->readMaterial( f );

        return 1;
    }

    //save materials
    bool ms3d_model_loader::writeMaterialSection( std::fstream *f )
    {
        ms3d_model_material_section h;
        uint16_t i;

        h.cnt = (uint16_t)this->mats.size();
        f->write( (char *)&h, sizeof( h ) );

        for( i = 0; i < h.cnt; i++ )
            this->writeMaterial( f, &this->mats[ i ] );

        return 1;
    }

    //load material
    bool ms3d_model_loader::readMaterial( std::fstream *f )
    {
        ms3d_model_material_m h;

        memset( &h, 0, sizeof( h ) );
        f->read( (char *)&h.f, sizeof( h.f ) );
        this->mats.push_back( h );
        
        return 1;
    }

    //save material
    bool ms3d_model_loader::writeMaterial( std::fstream *f, ms3d_model_material_m *h )
    {
        f->write( (char *)&h->f, sizeof( h->f ) );
        return 1;
    }

    //load animation section
    bool ms3d_model_loader::readAnimationSection( std::fstream *f )
    {
        ms3d_model_animation_section h;

        memset( &h, 0, sizeof( h ) );
        f->read( (char *)&h, sizeof( h ) );
        this->anim = h;

        return 1;
    }

    //save animation section
    bool ms3d_model_loader::writeAnimationSection( std::fstream *f )
    {
        f->write( (char *)&this->anim, sizeof( this->anim ) );
        return 1;
    }

    //load joint section
    bool ms3d_model_loader::readJointSection( std::fstream *f )
    {
        ms3d_model_joint_section h;
        uint16_t i;

        f->read( (char *)&h, sizeof( h ) );
        this->joints.clear();

        for( i = 0; i < h.cnt; i++ )
            this->readJoint( f );

        return 1;
    }

    //save joint section
    bool ms3d_model_loader::writeJointSection( std::fstream *f )
    {
        ms3d_model_joint_section h;
        uint16_t i;

        h.cnt = (uint16_t)this->joints.size();
        f->write( (char *)&h, sizeof( h ) );

        for( i = 0; i < h.cnt; i++ )
            this->writeJoint( f, &this->joints[ i ] );

        return 1;
    }

    //load joint
    bool ms3d_model_loader::readJoint( std::fstream *f )
    {
        ms3d_model_joint_m h;
        unsigned int i, e;

        memset( &h, 0, sizeof( h ) );
        f->read( (char *)&h.f, sizeof( h.f ) );

        e = h.f.cnt_rot_frames;
        for( i = 0; i < e; i++ )
            this->readJointKeyframe( f, &h.rotate_frames );
        e = h.f.cnt_pos_frames;
        for( i = 0; i < e; i++ )
            this->readJointKeyframe( f, &h.translate_frames );

        this->joints.push_back( h );

        return 1;
    }

    //save joint
    bool ms3d_model_loader::writeJoint( std::fstream *f, ms3d_model_joint_m *h )
    {
        unsigned int i, e;
        ms3d_model_joint_keyframe *k;

        h->f.cnt_rot_frames = h->rotate_frames.size();
        h->f.cnt_pos_frames = h->translate_frames.size();

        f->write( (char *)&h->f, sizeof( h->f ) );

        e = h->f.cnt_rot_frames;
        for( i = 0; i < e; i++ )
        {
            k = &h->rotate_frames[ i ];
            this->writeJointKeyframe( f, k );
        }

        e = h->f.cnt_pos_frames;
        for( i = 0; i < e; i++ )
        {
            k = &h->translate_frames[ i ];
            this->writeJointKeyframe( f, k );
        }

        return 1;
    }

    //load joint keyframe
    bool ms3d_model_loader::readJointKeyframe( std::fstream *f, std::vector<ms3d_model_joint_keyframe> *l )
    {
        ms3d_model_joint_keyframe h;

        memset( &h, 0, sizeof( h ) );
        f->read( (char *)&h, sizeof( h ) );

        l->push_back( h );
        return 1;
    }

    //save joint keyframe
    bool ms3d_model_loader::writeJointKeyframe( std::fstream *f, ms3d_model_joint_keyframe *h )
    {
        f->write( (char *)h, sizeof( ms3d_model_joint_keyframe ) );
        return 1;
    }

    //read comments section
    bool ms3d_model_loader::readCommentSection( std::fstream *f )
    {
        ms3d_model_comment_section cs;
        ms3d_model_comment_header h;
        ms3d_model_group_m *g;
        ms3d_model_material_m *m;
        ms3d_model_joint_m *j;
        std::string s;
        int i;

        f->read( (char *)&cs, sizeof( cs ) );
        if( cs.version != 1 )
            return 0;

        //group
        h.cnt = 0;
        f->read( (char *)&h, sizeof( h ) );
        for( i = 0; i < h.cnt; i++ )
        {
            this->readComment( f, &s );
            if( i >= this->groups.size() )
                continue;
            g = &this->groups[ i ];
            g->cmt.append( s );
        }

        //material
        h.cnt = 0;
        f->read( (char *)&h, sizeof( h ) );
        for( i = 0; i < h.cnt; i++ )
        {
            this->readComment( f, &s );
            if( i >= this->mats.size() )
                continue;
            m = &this->mats[ i ];
            m->cmt.append( s );
        }

        //joint
        h.cnt = 0;
        f->read( (char *)&h, sizeof( h ) );
        for( i = 0; i < h.cnt; i++ )
        {
            this->readComment( f, &s );
            if( i >= this->joints.size() )
                continue;
            j = &this->joints[ i ];
            j->cmt.append( s );
        }

        //model
        h.cnt = 0;
        f->read( (char *)&h, sizeof( h ) );
        for( i = 0; i < h.cnt; i++ )
        {
            this->readComment( f, &s );
            this->cmt.append( s );
        }

        return 1;
    }

    //write comments section
    bool ms3d_model_loader::writeCommentSection( std::fstream *f )
    {
        ms3d_model_comment_section cs;
        ms3d_model_comment_header h;
        ms3d_model_group_m *g;
        ms3d_model_material_m *m;
        ms3d_model_joint_m *j;
        std::string s;
        int i;

        cs.version = 1;
        f->write( (char *)&cs, sizeof( cs ) );

        //group
        h.cnt = (int)this->groups.size();
        f->write( (char *)&h, sizeof( h ) );
        for( i = 0; i < h.cnt; i++ )
        {
            g = &this->groups[ i ];
            this->writeComment( f, &g->cmt );
        }

        //material
        h.cnt = (int)this->mats.size();
        f->write( (char *)&h, sizeof( h ) );
        for( i = 0; i < h.cnt; i++ )
        {
            m = &this->mats[ i ];
            this->writeComment( f, &m->cmt );
        }

        //joint
        h.cnt = (int)this->joints.size();
        f->write( (char *)&h, sizeof( h ) );
        for( i = 0; i < h.cnt; i++ )
        {
            j = &this->joints[ i ];
            this->writeComment( f, &j->cmt );
        }

        //model
        h.cnt = 1;
        f->write( (char *)&h, sizeof( h ) );
        this->writeComment( f, &this->cmt );

        return 1;
    }

    //read comment
    bool ms3d_model_loader::readComment( std::fstream *f, std::string *s )
    {
        ms3d_model_comment d;
        union
        {
            ms3d_model_comment *c;
            char *b;
        };

        f->read( (char *)&d.h, sizeof( d.h ) );
        if( d.h.size < 0 )
            d.h.size = 0;
        if( d.h.size > 1024 )
            d.h.size = 1024;
        b = (char *)malloc( d.h.size + sizeof(ms3d_model_comment_prefix) + 1 );
        b[ d.h.size + sizeof(ms3d_model_comment_prefix) ] = 0;
        c->h = d.h;

        f->read( &c->data, d.h.size );
        s->assign( &c->data, d.h.size );

        free( b );
        return 1;
    }

    //write comment
    bool ms3d_model_loader::writeComment( std::fstream *f, std::string *s )
    {
        ms3d_model_comment_prefix h;
        char *c;

        h.size = (unsigned int)s->size();
        c = (char *)s->c_str();

        f->write( (char *)&h, sizeof( h ) );
        if( h.size )
            f->write( c, h.size );

        return 1;
    }


    //create vertexes
    void ms3d_model_loader::createVertexes( void )
    {
        model_vertex_ref *r;
        model_vertex_writelock *rl;
        shared_obj_guard g;
        dpxyzw x;
        unsigned int i, e;
        ms3d_model_vertex_m *v;

        e = (unsigned int)this->verts.size();
        for( i = 0; i < e; i++ )
        {
            v = &this->verts[ i ];

            r = this->m->createVertex( this->thd );
            if( !r )
                continue;
            rl = (model_vertex_writelock *)g.writeLock( r );
            if( !rl )
                continue;

            x.x = v->f.position.x;
            x.y = v->f.position.y;
            x.z = v->f.position.z;
            x.w = 1.0f;
            rl->setPosition( &x );
            v->id = rl->getId();

            delete r;
        }
    }

    //convert vertexes for saving
    void ms3d_model_loader::convertVertexes( void )
    {
        std::list<model_vertex_ref *> l;
        std::list<model_vertex_ref *>::iterator i;
        model_vertex_ref *r;
        model_vertex_readlock *rl;
        shared_obj_guard g;
        ms3d_model_vertex_m v;
        dpxyzw x;

        this->m->getVertexes( &l );
        this->verts.clear();
        memset( &v, 0, sizeof( v ) );

        for( i = l.begin(); i != l.end(); ++i )
        {
            r = *i;
            rl = (model_vertex_readlock *)g.readLock( r );
            if( !rl )
                continue;

            v.id = rl->getId();
            rl->getPosition( &x );
            v.f.position.x = x.x;
            v.f.position.y = x.y;
            v.f.position.z = x.z;
            v.f.flags = 0;
            v.f.boneId = 0;

            this->verts.push_back( v );
        }

        this->m->releaseGetVertexes( &l );
    }

    //create groups
    void ms3d_model_loader::createGroups( void )
    {
        model_group_ref *r;
        model_group_writelock *rl;
        shared_obj_guard g;
        unsigned int i, e;
        ms3d_model_group_m *v;
        std::string s;

        e = (unsigned int)this->groups.size();
        for( i = 0; i < e; i++ )
        {
            v = &this->groups[ i ];

            r = this->m->createGroup( this->thd );
            if( !r )
                continue;
            rl = (model_group_writelock *)g.writeLock( r );
            if( !rl )
                continue;

            s.assign( (char *)v->f.name, sizeof( v->f.name ) );
            rl->setName( &s );
            v->id = rl->getId();

            delete r;
        }
    }

    //convert groups
    void ms3d_model_loader::convertGroups( void )
    {
        std::list<model_group_ref *> l;
        std::list<model_group_ref *>::iterator i;
        model_group_ref *r;
        model_group_readlock *rl;
        shared_obj_guard g;
        ms3d_model_group_m v;
        std::string s;

        this->m->getGroups( &l );
        this->groups.clear();
        memset( &v, 0, sizeof( v ) );

        for( i = l.begin(); i != l.end(); ++i )
        {
            r = *i;
            rl = (model_group_readlock *)g.readLock( r );
            if( !rl )
                continue;

            v.id = rl->getId();
            rl->getName( &s );
            s.copy( (char *)v.f.name, sizeof( v.f.name ) );

            this->groups.push_back( v );
        }

        this->m->releaseGetGroups( &l );
    }

    //convert group triangles
    void ms3d_model_loader::convertGroupTriangles( void )
    {
        unsigned int i, e;
        ms3d_model_group_m *g;

        e = (unsigned int)this->groups.size();
        for( i = 0; i < e; i++ )
        {
            g = &this->groups[ i ];
            this->convertGroupTriangles( i, g );
        }
    }

    //convert group triangles
    void ms3d_model_loader::convertGroupTriangles( unsigned int gi, ms3d_model_group_m *g )
    {
        unsigned int i, e;
        ms3d_model_triangle_m *t;
        ms3d_model_group_triangle gt;

        g->triangles.clear();
        e = (unsigned int)this->tris.size();
        for( i = 0; i < e; i++ )
        {
            t = &this->tris[ i ];
            if( !dpid_compare( &t->group_id, &g->id ) )
                continue;
            t->f.groupIndex = gi;
            gt.index = i;
            g->triangles.push_back( gt );
        }
    }

    //find group containing triangle
    ms3d_model_group_m *ms3d_model_loader::findGroupHavingTriangle( unsigned int ti )
    {
        unsigned int i, e, j, k;
        ms3d_model_group_m *v;

        e = (unsigned int)this->groups.size();
        for( i = 0; i < e; i++ )
        {
            v = &this->groups[ i ];

            k = v->f.cntTriangles;
            for( j = 0; j < k; j++ )
            {
                if( v->triangles[ j ].index == ti )
                    return v;
            }
        }

        return 0;
    }

    //create triangles
    void ms3d_model_loader::createTriangles( void )
    {
        model_triangle_ref *r;
        model_triangle_writelock *rl;
        shared_obj_guard g;
        unsigned int i, e;
        ms3d_model_triangle_m *v;
        ms3d_model_group_m *gm;

        e = (unsigned int)this->tris.size();
        for( i = 0; i < e; i++ )
        {
            v = &this->tris[ i ];

            gm = this->findGroupHavingTriangle( i );
            if( !gm )
                continue;
            v->group_id = gm->id;

            r = this->m->createTriangle( this->thd, gm->id );
            if( !r )
                continue;
            rl = (model_triangle_writelock *)g.writeLock( r );
            if( !rl )
                continue;
            v->id = rl->getId();

            this->createTriangleVertexes( v );

            delete r;
        }
    }

    //convert triangles
    void ms3d_model_loader::convertTriangles( void )
    {
        std::list<model_triangle_ref *> l;
        std::list<model_triangle_ref *>::iterator i;
        model_triangle_ref *r;
        model_triangle_readlock *rl;
        shared_obj_guard g;
        ms3d_model_triangle_m v;

        this->m->getTriangles( &l );
        this->tris.clear();
        memset( &v, 0, sizeof( v ) );

        for( i = l.begin(); i != l.end(); ++i )
        {
            r = *i;
            rl = (model_triangle_readlock *)g.readLock( r );
            if( !rl )
                continue;

            v.id = rl->getId();
            this->tris.push_back( v );
            v.f.groupIndex = 0;
            v.group_id = rl->getParentId();

            this->convertTriangleVertexes( &v );
        }

        this->m->releaseGetTriangles( &l );
    }

    //create triangle vertexes
    void ms3d_model_loader::createTriangleVertexes( ms3d_model_triangle_m *t )
    {
        unsigned int i, e;
        ms3d_model_vertex_m *v;
        dpxyzw n;
        dpst tx;

        e = (unsigned int)this->verts.size();

        i = t->f.verticies[ 0 ];
        if( i >= e )
            i = 0;
        v = &this->verts[ i ];
        n.x = t->f.normals[ 0 ].x;
        n.y = t->f.normals[ 0 ].y;
        n.z = t->f.normals[ 0 ].z;
        n.w = 1.0f;
        tx.s = t->f.s[ 0 ];
        tx.t = t->f.t[ 0 ];
        this->createTriangleVertex( t, v, &n, &tx, &tx );

        i = t->f.verticies[ 1 ];
        if( i >= e )
            i = 0;
        v = &this->verts[ i ];
        n.x = t->f.normals[ 1 ].x;
        n.y = t->f.normals[ 1 ].y;
        n.z = t->f.normals[ 1 ].z;
        n.w = 1.0f;
        tx.s = t->f.s[ 1 ];
        tx.t = t->f.t[ 1 ];
        this->createTriangleVertex( t, v, &n, &tx, &tx );

        i = t->f.verticies[ 2 ];
        if( i >= e )
            i = 0;
        v = &this->verts[ i ];
        n.x = t->f.normals[ 2 ].x;
        n.y = t->f.normals[ 2 ].y;
        n.z = t->f.normals[ 2 ].z;
        n.w = 1.0f;
        tx.s = t->f.s[ 2 ];
        tx.t = t->f.t[ 2 ];
        this->createTriangleVertex( t, v, &n, &tx, &tx );
    }

    //convert triangle vertexes
    void ms3d_model_loader::convertTriangleVertexes( ms3d_model_triangle_m *t )
    {
        std::list<model_triangle_vertex_ref *> l;
        std::list<model_triangle_vertex_ref *>::iterator i;
        model_triangle_vertex_ref *r;
        unsigned int vi;

        this->m->getTriangleVertexesByTriangle( &l, t->id );

        i = l.begin();
        vi = 0;

        if( i != l.end() )
        {
            r = *i;
            this->convertTriangleVertex( t, vi, r );
            ++i;
            vi++;
        }
        if( i != l.end() )
        {
            r = *i;
            this->convertTriangleVertex( t, vi, r );
            ++i;
            vi++;
        }
        if( i != l.end() )
        {
            r = *i;
            this->convertTriangleVertex( t, vi, r );
            ++i;
            vi++;
        }

        this->m->releaseGetTriangleVertexes( &l );
    }

    //find offset for vertex by id
    unsigned int ms3d_model_loader::findVertex( dpid id )
    {
        unsigned int i, e;
        ms3d_model_vertex_m *v;

        e = (unsigned int)this->verts.size();
        for( i = 0; i < e; i++ )
        {
            v = &this->verts[ i ];
            if( dpid_compare( &id, &v->id ) )
                return i;
        }

        return 0;
    }

    //create triangle vertex
    void ms3d_model_loader::createTriangleVertex( ms3d_model_triangle_m *t, ms3d_model_vertex_m *v, dpxyzw *n, dpst *t0, dpst *t1 )
    {
        model_triangle_vertex_ref *r;
        model_triangle_vertex_writelock *rl;
        shared_obj_guard g;

        r = this->m->createTriangleVertex( this->thd, t->id, v->id );
        if( !r )
            return;
        rl = (model_triangle_vertex_writelock *)g.writeLock( r );
        delete r;
        if( !rl )
            return;

        rl->setNormal( n );
        rl->setTexcoord( 0, t0 );
        rl->setTexcoord( 0, t1 );
    }

        //convert triangle vertex
    void ms3d_model_loader::convertTriangleVertex( ms3d_model_triangle_m *t, unsigned int vi, model_triangle_vertex_ref *v )
    {
        model_triangle_vertex_readlock *rl;
        shared_obj_guard g;
        dpxyzw n;
        dpst tx;

        if( !v )
            return;
        rl = (model_triangle_vertex_readlock *)g.readLock( v );
        if( !rl )
            return;

        rl->getNormal( &n );
        t->f.normals[ vi ].x = n.x;
        t->f.normals[ vi ].y = n.y;
        t->f.normals[ vi ].z = n.z;
        rl->getTexcoord( 0, &tx );
        t->f.s[ vi ] = tx.s;
        t->f.t[ vi ] = tx.t;
        t->f.verticies[ vi ] = this->findVertex( rl->getVertexId() );
    }

};
