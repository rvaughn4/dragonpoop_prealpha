
#include "ms3d_model_loader.h"
#include "../../dpvertex/dpvertexes.h"
#include "../../../core/shared_obj/shared_obj_guard.h"
#include "../model_vertex/model_vertexes.h"
#include "../model_group/model_groups.h"
#include "../model_triangle/model_triangles.h"
#include "../model_triangle_vertex/model_triangle_vertexes.h"
#include "../model_joint/model_joints.h"
#include "../model_animation/model_animations.h"
#include "../model_animation_frame/model_animation_frames.h"
#include "../model_frame/model_frames.h"
#include "../model_frame_joint/model_frame_joints.h"
#include "../model_vertex_joint/model_vertex_joints.h"
#include "../model_material/model_materials.h"
#include "../../dpbitmap/dpbitmaps.h"
#include <sstream>

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

        l.fname.assign( fname );
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

        if( l.readCommentSection( &f ) )
        if( l.readVertexExtraSection( &f ) )
        if( l.readJointExtraSection( &f ) )
            l.readModelExtra( &f );

        l.createAnimation();
        l.createFrames();
        l.createJoints();
        l.createFrameJoints();
        l.createMaterials();
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

        l.fname.assign( fname );
        f.open( fname, f.binary | f.out | f.trunc );
        if( !f.is_open() )
            return 0;

        l.convertFrames();
        l.convertAnimation();
        l.convertJoints();
        l.convertFrameJoints();
        l.convertMaterials();
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

        if( l.writeCommentSection( &f ) )
        if( l.writeVertexExtraSection( &f ) )
        if( l.writeJointExtraSection( &f ) )
            l.writeModelExtra( &f );

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
        h.time = h.time * this->anim.fps;

        l->push_back( h );
        return 1;
    }

    //save joint keyframe
    bool ms3d_model_loader::writeJointKeyframe( std::fstream *f, ms3d_model_joint_keyframe *h )
    {
        h->time = h->time / this->anim.fps;
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

    //read vertex extra section
    bool ms3d_model_loader::readVertexExtraSection( std::fstream *f )
    {
        ms3d_model_vertex_extra_section h;
        ms3d_model_vertex_m *v;
        unsigned int i, c;

        f->read( (char *)&h, sizeof( h ) );
        if( h.version < 1 || h.version > 2 )
            return 0;

        c = (unsigned int)this->verts.size();
        for( i = 0; i < c; i++ )
        {
            v = &this->verts[ i ];
            this->readVertexExtra( f, v, &h );
        }

        return 1;
    }

    //write vertex extra section
    bool ms3d_model_loader::writeVertexExtraSection( std::fstream *f )
    {
        ms3d_model_vertex_extra_section h;
        ms3d_model_vertex_m *v;
        unsigned int i, c;

        h.version = 1;
        f->write( (char *)&h, sizeof( h ) );

        c = (unsigned int)this->verts.size();
        for( i = 0; i < c; i++ )
        {
            v = &this->verts[ i ];
            this->writeVertexExtra( f, v, &h );
        }

        return 1;
    }

    //read vertex extra
    bool ms3d_model_loader::readVertexExtra( std::fstream *f, ms3d_model_vertex_m *v, ms3d_model_vertex_extra_section *eh )
    {
        ms3d_model_vertex_extra_v2 h;

        switch( eh->version )
        {
            case 1:
                f->read( (char *)&h.v, sizeof( h.v ) );
                break;
            case 2:
                f->read( (char *)&h, sizeof( h ) );
                break;
            default:
                return 0;
        }

        v->bones[ 0 ].id = h.v.bones[ 0 ];
        v->bones[ 0 ].weight = h.v.weights[ 0 ];
        v->bones[ 1 ].id = h.v.bones[ 1 ];
        v->bones[ 1 ].weight = h.v.weights[ 1 ];
        v->bones[ 2 ].id = h.v.bones[ 2 ];
        v->bones[ 2 ].weight = h.v.weights[ 2 ];
        return 1;
    }

    //write vertex extra
    bool ms3d_model_loader::writeVertexExtra( std::fstream *f, ms3d_model_vertex_m *v, ms3d_model_vertex_extra_section *eh )
    {
        ms3d_model_vertex_extra_v2 h;

        h.extra = 0;
        h.v.bones[ 0 ] = v->bones[ 0 ].id;
        h.v.weights[ 0 ] = v->bones[ 0 ].weight;
        h.v.bones[ 1 ] = v->bones[ 1 ].id;
        h.v.weights[ 1 ] = v->bones[ 1 ].weight;
        h.v.bones[ 2 ] = v->bones[ 2 ].id;
        h.v.weights[ 2 ] = v->bones[ 2 ].weight;

        switch( eh->version )
        {
            case 1:
                f->write( (char *)&h.v, sizeof( h.v ) );
                break;
            case 2:
                f->write( (char *)&h, sizeof( h ) );
                break;
            default:
                return 0;
        }

        return 1;
    }

    //read joint extra section
    bool ms3d_model_loader::readJointExtraSection( std::fstream *f )
    {
        ms3d_model_joint_extra_section h;
        ms3d_model_joint_m *v;
        unsigned int i, c;

        f->read( (char *)&h, sizeof( h ) );
        if( h.version != 1 )
            return 0;

        c = (unsigned int)this->joints.size();
        for( i = 0; i < c; i++ )
        {
            v = &this->joints[ i ];
            this->readJointExtra( f, v, &h );
        }

        return 1;
    }

    //write vertex extra section
    bool ms3d_model_loader::writeJointExtraSection( std::fstream *f )
    {
        ms3d_model_joint_extra_section h;
        ms3d_model_joint_m *v;
        unsigned int i, c;

        h.version = 1;
        f->write( (char *)&h, sizeof( h ) );

        c = (unsigned int)this->joints.size();
        for( i = 0; i < c; i++ )
        {
            v = &this->joints[ i ];
            this->writeJointExtra( f, v, &h );
        }
        
        return 1;
    }

    //read joint extra
    bool ms3d_model_loader::readJointExtra( std::fstream *f, ms3d_model_joint_m *v, ms3d_model_joint_extra_section *eh )
    {
        ms3d_model_joint_extra h;

        if( eh->version != 1 )
            return 0;
        f->read( (char *)&h, sizeof( h ) );
        v->e = h;

        return 1;
    }

    //write joint extra
    bool ms3d_model_loader::writeJointExtra( std::fstream *f, ms3d_model_joint_m *v, ms3d_model_joint_extra_section *eh )
    {
        ms3d_model_joint_extra h;

        if( eh->version != 1 )
            return 0;
        h = v->e;
        f->write( (char *)&h, sizeof( h ) );

        return 1;
    }

    //read model extra
    bool ms3d_model_loader::readModelExtra( std::fstream *f )
    {
        ms3d_model_extra h;

        f->read( (char *)&h, sizeof( h ) );
        this->ext = h;

        return 1;
    }

    //write model extra
    bool ms3d_model_loader::writeModelExtra( std::fstream *f )
    {
        ms3d_model_extra h;

        h = this->ext;
        f->write( (char *)&h, sizeof( h ) );

        return 1;
    }

    //create materials
    void ms3d_model_loader::createMaterials( void )
    {
        model_material_ref *r;
        model_material_writelock *rl;
        shared_obj_guard g;
        unsigned int i, e;
        ms3d_model_material_m *v;
        dprgba c;
        std::string s;
        dpbitmap b;

        e = (unsigned int)this->mats.size();
        for( i = 0; i < e; i++ )
        {
            v = &this->mats[ i ];

            r = this->m->createMaterial( this->thd );
            if( !r )
                continue;
            rl = (model_material_writelock *)g.writeLock( r );
            delete r;
            if( !rl )
                continue;

            v->id = rl->getId();

            c.r = v->f.colors.diffuse.r;
            c.g = v->f.colors.diffuse.g;
            c.b = v->f.colors.diffuse.b;
            c.a = v->f.colors.diffuse.a;
            rl->setDiffuse( &c );

            //spec
            c.r = v->f.colors.specular.r;
            c.g = v->f.colors.specular.g;
            c.b = v->f.colors.specular.b;
            c.a = v->f.colors.specular.a;
            rl->setSpecular( &c );

            //emiss
            c.r = v->f.colors.emissive.r;
            c.g = v->f.colors.emissive.g;
            c.b = v->f.colors.emissive.b;
            c.a = v->f.colors.emissive.a;
            rl->setEmmissive( &c );

            //ambient
            c.r = v->f.colors.ambient.r;
            c.g = v->f.colors.ambient.g;
            c.b = v->f.colors.ambient.b;
            c.a = v->f.colors.ambient.a;
            rl->setAmbient( &c );

            rl->setShine( v->f.shininess );
            rl->setOpacity( v->f.transparency );

            s.assign( (char *)v->f.name, sizeof(v->f.name) );
            rl->setName( &s );

            b.reset();
            s.assign( (char *)v->f.tex_filename, sizeof(v->f.tex_filename) );
            s.assign( "felhound_green.bmp" );
            if( s.length() < 1 )
                continue;
            if( !b.loadFile( s.c_str() ) )
                continue;
            rl->setDiffuseTexture( &b );

            b.reset();
            s.assign( (char *)v->f.alpha_filename, sizeof(v->f.alpha_filename) );
            if( s.length() < 1 )
                continue;
            if( !b.loadFile( s.c_str() ) )
                continue;
            rl->setAlphaMapTexture( &b );
        }
    }

    //convert materials
    void ms3d_model_loader::convertMaterials( void )
    {
        std::list<model_material_ref *> l;
        std::list<model_material_ref *>::iterator i;
        model_material_ref *r;
        model_material_readlock *rl;
        shared_obj_guard g;
        ms3d_model_material_m v;
        dprgba c;
        std::string s;
        dpbitmap b;

        this->m->getMaterials( &l );
        this->mats.clear();

        for( i = l.begin(); i != l.end(); ++i )
        {
            r = *i;
            rl = (model_material_readlock *)g.readLock( r );
            if( !rl )
                continue;

            memset( &v, 0, sizeof( v ) );
            v.id = rl->getId();

            //diff
            rl->getDiffuse( &c );
            v.f.colors.diffuse.r = c.r;
            v.f.colors.diffuse.g = c.g;
            v.f.colors.diffuse.b = c.b;
            v.f.colors.diffuse.a = c.a;

            //spec
            rl->getSpecular( &c );
            v.f.colors.specular.r = c.r;
            v.f.colors.specular.g = c.g;
            v.f.colors.specular.b = c.b;
            v.f.colors.specular.a = c.a;

            //emiss
            rl->getEmmissive( &c );
            v.f.colors.emissive.r = c.r;
            v.f.colors.emissive.g = c.g;
            v.f.colors.emissive.b = c.b;
            v.f.colors.emissive.a = c.a;

            //ambient
            rl->getAmbient( &c );
            v.f.colors.ambient.r = c.r;
            v.f.colors.ambient.g = c.g;
            v.f.colors.ambient.b = c.b;
            v.f.colors.ambient.a = c.a;

            v.f.shininess = rl->getShine();
            v.f.transparency = rl->getOpacity();

            rl->getName( &s );
            s.copy( (char *)v.f.name, sizeof(v.f.name) );

            if( rl->getDiffuseTexture( &b ) )
            {
                std::stringstream ss;
                ss << this->fname << "." << (const char *)v.f.name << ".diffuse.bmp";
                s = ss.str();
                b.saveFile( s.c_str() );
                s.copy( (char *)v.f.tex_filename, sizeof( v.f.tex_filename ) );
            }

            if( rl->getAlphaMapTexture( &b ) )
            {
                std::stringstream ss;
                ss << this->fname << "." << (const char *)v.f.name << ".alphamask.bmp";
                s = ss.str();
                b.saveFile( s.c_str() );
                s.copy( (char *)v.f.tex_filename, sizeof( v.f.tex_filename ) );
            }

            if( rl->getBumpMapTexture( &b ) )
            {
                std::stringstream ss;
                ss << this->fname << "." << (const char *)v.f.name << ".bumpmap.bmp";
                s = ss.str();
                b.saveFile( s.c_str() );
                s.copy( (char *)v.f.tex_filename, sizeof( v.f.tex_filename ) );
            }

            if( rl->getSpecularMapTexture( &b ) )
            {
                std::stringstream ss;
                ss << this->fname << "." << (const char *)v.f.name << ".specularmap.bmp";
                s = ss.str();
                b.saveFile( s.c_str() );
                s.copy( (char *)v.f.tex_filename, sizeof( v.f.tex_filename ) );
            }

            this->mats.push_back( v );
        }
        
        this->m->releaseGetMaterials( &l );
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

            this->createVertexJoints( v );

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

            this->convertVertexJoints( &v );

            this->verts.push_back( v );
        }

        this->m->releaseGetVertexes( &l );
    }

    //create vertex joints
    void ms3d_model_loader::createVertexJoints( ms3d_model_vertex_m *v )
    {
        this->createVertexJoint( v, v->f.boneId, 1.0f );
        this->createVertexJoint( v, v->bones[ 0 ].id, v->bones[ 0 ].weight / 100.0f );
        this->createVertexJoint( v, v->bones[ 1 ].id, v->bones[ 1 ].weight / 100.0f );
        this->createVertexJoint( v, v->bones[ 2 ].id, v->bones[ 2 ].weight / 100.0f );
    }

    //convert vertex joints
    void ms3d_model_loader::convertVertexJoints( ms3d_model_vertex_m *v )
    {
        std::list<model_vertex_joint_ref *> l;
        std::list<model_vertex_joint_ref *>::iterator i;
        model_vertex_joint_ref *p;
        unsigned int cnt;

        this->m->getVertexJointsByVertex( &l, v->id );

        for( cnt = 0, i = l.begin(); i != l.end(); ++i, cnt++ )
        {
            p = *i;
            this->convertVertexJoint( v, p, cnt );
        }

        this->m->releaseGetVertexJoints( &l );
    }

    //create vertex joint
    void ms3d_model_loader::createVertexJoint( ms3d_model_vertex_m *v, int jindex, float w )
    {
        model_vertex_joint_ref *r;
        model_vertex_joint_writelock *rl;
        ms3d_model_joint_m *j;
        shared_obj_guard o;

        if( jindex < 0 || jindex >= this->joints.size() )
            return;
        if( w <= 0.0f )
            return;
        j = &this->joints[ jindex ];

        r = this->m->createVertexJoint( this->thd, v->id, j->id );
        if( !r )
            return;
        rl = (model_vertex_joint_writelock *)o.writeLock( r );
        delete r;
        if( !rl )
            return;

        rl->setWeight( w );
    }

    //convert vertex joint
    void ms3d_model_loader::convertVertexJoint( ms3d_model_vertex_m *v, model_vertex_joint_ref *r, unsigned int cnt )
    {
        unsigned int i, c, f;
        ms3d_model_joint_m *j;
        model_vertex_joint_readlock *rl;
        shared_obj_guard o;
        dpid id;

        if( !r )
            return;
        rl = (model_vertex_joint_readlock *)o.readLock( r );
        if( !rl )
            return;
        id = rl->getJointId();

        c = (unsigned int)this->joints.size();
        for( f = c, i = 0; i < c && f >= c; i++ )
        {
            j = &this->joints[ i ];
            if( dpid_compare( &j->id, &id ) )
                f = i;
        }
        if( f >= c )
            return;

        if( cnt > 3 )
            return;
        if( cnt == 0 )
        {
            v->f.boneId = f;
            return;
        }
        v->bones[ cnt - 1 ].id = f;
        v->bones[ cnt - 1 ].weight = rl->getWeight() * 100.0f;
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

            if( v->e.index >= 0 && v->e.index < this->mats.size() )
                rl->setMaterialId( this->mats[ v->e.index ].id );

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
            v.e.index = this->findMaterial( rl->getMaterialId() );

            this->groups.push_back( v );
        }

        this->m->releaseGetGroups( &l );
    }

    //find material having id
    int ms3d_model_loader::findMaterial( dpid id )
    {
        unsigned int i, e;
        ms3d_model_material_m *v;

        e = (unsigned int)this->mats.size();
        for( i = 0; i < e; i++ )
        {
            v = &this->mats[ i ];
            if( dpid_compare( &v->id, &id ) )
                return i;
        }

        return -1;
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

    //create frames
    void ms3d_model_loader::createFrames( void )
    {
        ms3d_model_frame f;
        std::vector<float> d, e;
        unsigned int i, c, j, k, l;
        ms3d_model_joint_m *jt;
        ms3d_model_joint_keyframe *kf;

        c = (unsigned int)this->joints.size();
        for( i = 0; i < c; i++ )
        {
            jt = &this->joints[ i ];

            k = (unsigned int)jt->translate_frames.size();
            for( j = 0; j < k; j++ )
            {
                kf = &jt->translate_frames[ j ];
                d.push_back( kf->time );
            }

            k = (unsigned int)jt->rotate_frames.size();
            for( j = 0; j < k; j++ )
            {
                kf = &jt->rotate_frames[ j ];
                d.push_back( kf->time );
            }
        }

        c = (unsigned int)d.size();
        for( i = 0; i < c; i++ )
        {
            k = (unsigned int)e.size();
            l = 0;
            for( j = 0; j < k; j++ )
            {
                if( d[ i ] == e[ j ] )
                    l++;
            }
            if( !l )
                e.push_back( d[ i ] );
        }
        //std::sort( e.begin(), e.end() );

        this->highest_frame = 0;
        c = (unsigned int)e.size();
        for( i = 0; i < c; i++ )
        {
            f.t = e[ i ];
            this->createFrame( &f );
            this->frames.push_back( f );
            if( f.t > this->highest_frame )
                this->highest_frame = f.t;
        }
    }

    //convert frames
    void ms3d_model_loader::convertFrames( void )
    {
        std::list<model_animation_frame_ref *> l;
        std::list<model_animation_frame_ref *>::iterator li;
        model_animation_frame_ref *p;
        model_animation_frame_readlock *pl;
        shared_obj_guard o;
        ms3d_model_frame f;

        this->anim_id = this->m->getDefaultAnimationId();
        this->m->getAnimationFramesByAnimation( &l, this->anim_id );

        this->highest_frame = 0;
        for( li = l.begin(); li != l.end(); ++li )
        {
            p = *li;
            pl = (model_animation_frame_readlock *)o.readLock( p );
            f.t = pl->getTime();
            f.id = pl->getFrameId();
            f.afid = pl->getId();
            this->frames.push_back( f );
            if( f.t > this->highest_frame )
                this->highest_frame = f.t;
        }

        this->m->releaseGetAnimationFrames( &l );
    }

    //create frame
    void ms3d_model_loader::createFrame( ms3d_model_frame *f )
    {
        model_frame_ref *fr;
        model_frame_writelock *frl;
        model_animation_frame_ref *ar;
        model_animation_frame_writelock *arl;
        shared_obj_guard o;
        std::stringstream ss;
        std::string s;

        fr = this->m->createFrame( this->thd );
        if( !fr )
            return;
        frl = (model_frame_writelock *)o.writeLock( fr );
        delete fr;
        if( !frl )
            return;

        ss << "MS3D Imported Frame #" << f->t << "";
        s = ss.str();
        frl->setName( &s );
        f->id = frl->getId();

        ar = this->m->createAnimationFrame( this->thd, this->anim_id, f->id, f->t );
        if( !ar )
            return;
        arl = (model_animation_frame_writelock *)o.writeLock( ar );
        delete ar;
        if( !arl )
            return;

        f->afid = arl->getId();
    }

    //create joints
    void ms3d_model_loader::createJoints( void )
    {
        ms3d_model_joint_m *j;
        unsigned int i, c;

        c = (unsigned int)this->joints.size();
        for( i = 0; i < c; i++ )
        {
           j = &this->joints[ i ];
           this->createJoint( j );
        }
    }

    //convert joints
    void ms3d_model_loader::convertJoints( void )
    {
        std::list<model_joint_ref *> l;
        std::list<model_joint_ref *>::iterator i;
        model_joint_ref *r;

        this->m->getJoints( &l );
        this->joints.clear();

        for( i = l.begin(); i != l.end(); ++i )
        {
            r = *i;
            this->convertJoint( r );
        }

        this->m->releaseGetJoints( &l );
    }

    //create joint
    void ms3d_model_loader::createJoint( ms3d_model_joint_m *j )
    {
        model_joint_ref *r;
        model_joint_writelock *l;
        shared_obj_guard g;
        std::string s;
        dpxyzw x;
        ms3d_model_joint_m *p;

        if( !dpid_isZero( &j->id ) )
            return;

        p = this->findJointParent( j );
        if( p )
            this->createJoint( p );

        if( p )
            r = this->m->createJoint( this->thd, p->id );
        else
            r = this->m->createJoint( this->thd );
        if( !r )
            return;
        l = (model_joint_writelock *)g.writeLock( r );
        delete r;
        if( !l )
            return;

        s.assign( (char *)j->f.name, sizeof( j->f.name ) );
        l->setName( &s );

        x.x = j->f.pos.x;
        x.y = j->f.pos.y;
        x.z = j->f.pos.z;
        x.w = 1.0f;
        l->setPosition( &x );

        x.x = j->f.rot.x;
        x.y = j->f.rot.y;
        x.z = j->f.rot.z;
        x.w = 1.0f;
        l->setRotation( &x );

        j->id = l->getId();
    }

    //convert joint
    void ms3d_model_loader::convertJoint( model_joint_ref *r )
    {
        model_joint_ref *rp;
        model_joint_readlock *rl, *rpl;
        shared_obj_guard g, gp;
        ms3d_model_joint_m v;
        std::string s;
        dpxyzw x;

        rl = (model_joint_readlock *)g.readLock( r );
        if( !rl )
            return;

        rp = rl->getParent();
        if( !rp )
            rpl = 0;
        else
        {
            rpl = (model_joint_readlock *)gp.readLock( rp );
            delete rp;
        }
        memset( &v, 0, sizeof( v ) );

        rl->getName( &s );
        s.copy( (char *)&v.f.name, sizeof( v.f.name ) );

        if( rpl )
        {
            rpl->getName( &s );
            s.copy( (char *)&v.f.parent_name, sizeof( v.f.parent_name ) );
        }

        rl->getPosition( &x );
        v.f.pos.x = x.x;
        v.f.pos.y = x.y;
        v.f.pos.z = x.z;

        rl->getRotation( &x );
        v.f.rot.x = x.x;
        v.f.rot.y = x.y;
        v.f.rot.z = x.z;

        v.id = rl->getId();

        this->joints.push_back( v );
    }

    //find parent joint
    ms3d_model_joint_m *ms3d_model_loader::findJointParent( ms3d_model_joint_m *a )
    {
        unsigned int i, c;
        std::string sa, sb;
        ms3d_model_joint_m *b;

        if( !a->f.name[ 0 ] )
            return 0;
        sa.assign( (char *)a->f.parent_name, sizeof( a->f.parent_name ) );

        c = (unsigned int)this->joints.size();
        for( i = 0; i < c; i++ )
        {
            b = &this->joints[ i ];
            sb.assign( (char *)b->f.name, sizeof( b->f.name ) );
            if( sa.compare( sb ) == 0 )
                return b;
        }

        return 0;
    }

    //create animation
    void ms3d_model_loader::createAnimation( void )
    {
        model_animation_ref *r;
        model_animation_writelock *rl;
        shared_obj_guard o;
        std::string s;

        r = this->m->createAnimation( this->thd );
        if( !r )
            return;
        rl = (model_animation_writelock *)o.writeLock( r );
        delete r;

        s.assign( "Imported MS3D Animation" );
        rl->setName( &s );
        rl->setAutoPlay( 1 );
        rl->setRepeatDelay( 100 );
        rl->setRepeated( 1 );
        rl->setSpeed( this->anim.fps );

        this->anim_id = rl->getId();
        this->m->setDefaultAnimationId( this->anim_id );
    }

    //convert animation
    void ms3d_model_loader::convertAnimation( void )
    {
        model_animation_ref *r;
        model_animation_readlock *rl;
        shared_obj_guard o;

        r = this->m->getDefaultAnimation();
        if( !r )
            return;
        rl = (model_animation_readlock *)o.readLock( r );
        delete r;

        this->anim_id = rl->getId();
        this->anim.fps = rl->getSpeed();
        this->anim.cnt_frames = (unsigned int)this->highest_frame + 1;
        this->anim.current_time = 0;
    }

    //create keyframes/frame_joints
    void ms3d_model_loader::createFrameJoints( void )
    {
        unsigned int i, c, l, d;
        ms3d_model_frame *f;
        ms3d_model_joint_m *j;

        c = (unsigned int)this->joints.size();
        for( i = 0; i < c; i++ )
        {
            j = &this->joints[ i ];
            d = (unsigned int)this->frames.size();
            for( l = 0; l < d; l++ )
            {
                f = &this->frames[ l ];
                this->createFrameJoint( j, f );
            }
        }
    }

    //convert keyframes/frame_joints
    void ms3d_model_loader::convertFrameJoints( void )
    {
        unsigned int i, c, l, d;
        ms3d_model_frame *f;
        ms3d_model_joint_m *j;

        c = (unsigned int)this->joints.size();
        for( i = 0; i < c; i++ )
        {
            j = &this->joints[ i ];
            d = (unsigned int)this->frames.size();
            for( l = 0; l < d; l++ )
            {
                f = &this->frames[ l ];
                this->convertFrameJoint( j, f );
            }
        }
    }

    //create keyframe/frame_joint for joint at frame
    void ms3d_model_loader::createFrameJoint( ms3d_model_joint_m *j, ms3d_model_frame *f )
    {
        ms3d_model_joint_keyframe trans, rot;
        model_frame_joint_ref *r;
        model_frame_joint_writelock *rl;
        shared_obj_guard o;
        dpxyzw x;

        this->findKeyFrameAtTime( j, f, &trans, &rot );

        r = this->m->createFrameJoint( this->thd, f->id, j->id );
        if( !r )
            return;
        rl = (model_frame_joint_writelock *)o.writeLock( r );
        delete r;
        if( !rl )
            return;

        x.x = trans.x;
        x.y = trans.y;
        x.z = trans.z;
        x.w = 1.0f;
        rl->setPosition( &x );

        x.x = rot.x;
        x.y = rot.y;
        x.z = rot.z;
        x.w = 1.0f;
        rl->setRotation( &x );
    }

    //convert keyframe/frame_joint for joint at frame
    void ms3d_model_loader::convertFrameJoint( ms3d_model_joint_m *j, ms3d_model_frame *f )
    {
        std::list<model_frame_joint_ref *> l;
        std::list<model_frame_joint_ref *>::iterator i;
        model_frame_joint_ref *r;
        model_frame_joint_readlock *rl;
        shared_obj_guard o;
        ms3d_model_joint_keyframe kf;
        dpxyzw x;

        this->m->getFrameJointsByFrameAndJoint( &l, f->id, j->id );

        for( i = l.begin(); i != l.end(); ++i )
        {
            r = *i;
            rl = (model_frame_joint_readlock *)o.readLock( r );
            if( !rl )
                continue;

            kf.time = f->t;

            rl->getPosition( &x );
            kf.x = x.x;
            kf.y = x.y;
            kf.z = x.z;
            j->translate_frames.push_back( kf );

            rl->getRotation( &x );
            kf.x = x.x;
            kf.y = x.y;
            kf.z = x.z;
            j->rotate_frames.push_back( kf );
        }
        o.unlock();

        this->m->releaseGetFrameJoints( &l );
    }

    //find translation and rotation at frame time for joint
    void ms3d_model_loader::findKeyFrameAtTime( ms3d_model_joint_m *j, ms3d_model_frame *f, ms3d_model_joint_keyframe *trans, ms3d_model_joint_keyframe *rot )
    {
        ms3d_model_joint_keyframe t0, t1, r0, r1;
        float m0, m1, d;

        this->findKeyFrameBeforeTime( j, f, &t0, &r0 );
        this->findKeyFrameAfterTime( j, f, &t1, &r1 );

        d = t1.time - t0.time;
        if( d - 0.0f < 0.01f )
            d = 1.0f;
        m1 = ( f->t - t0.time ) / d;
        m0 = 1.0f - m1;
        trans->time = f->t;
        trans->x = t0.x * m0 + t1.x * m1;
        trans->y = t0.y * m0 + t1.y * m1;
        trans->z = t0.z * m0 + t1.z * m1;

        d = r1.time - r0.time;
        if( d - 0.0f < 0.01f )
            d = 1.0f;
        m1 = ( f->t - r0.time ) / d;
        m0 = 1.0f - m1;
        rot->time = f->t;
        rot->x = r0.x * m0 + r1.x * m1;
        rot->y = r0.y * m0 + r1.y * m1;
        rot->z = r0.z * m0 + r1.z * m1;
    }

    //find keyframes before time
    void ms3d_model_loader::findKeyFrameBeforeTime( ms3d_model_joint_m *j, ms3d_model_frame *f, ms3d_model_joint_keyframe *trans, ms3d_model_joint_keyframe *rot )
    {
        unsigned int i, c;
        ms3d_model_joint_keyframe *r;

        rot->x = rot->y = rot->z = rot->time = 0;
        c = (unsigned int)j->rotate_frames.size();
        for( i = 0; i < c; i++ )
        {
            r = &j->rotate_frames[ i ];
            if( r->time > f->t )
                continue;
            if( r->time < rot->time )
                continue;
            rot->time = r->time;
            rot->x = r->x;
            rot->y = r->y;
            rot->z = r->z;
        }

        trans->x = trans->y = trans->z = trans->time = 0;
        c = (unsigned int)j->translate_frames.size();
        for( i = 0; i < c; i++ )
        {
            r = &j->translate_frames[ i ];
            if( r->time > f->t )
                continue;
            if( r->time < trans->time )
                continue;
            trans->time = r->time;
            trans->x = r->x;
            trans->y = r->y;
            trans->z = r->z;
        }
    }

    //find keyframes after time
    void ms3d_model_loader::findKeyFrameAfterTime( ms3d_model_joint_m *j, ms3d_model_frame *f, ms3d_model_joint_keyframe *trans, ms3d_model_joint_keyframe *rot )
    {
        unsigned int i, c;
        ms3d_model_joint_keyframe *r;

        this->findKeyFrameBeforeTime( j, f, trans, rot );

        c = (unsigned int)j->rotate_frames.size();
        for( i = 0; i < c; i++ )
        {
            r = &j->rotate_frames[ i ];
            if( r->time < f->t )
                continue;
            if( r->time > rot->time )
                continue;
            rot->time = r->time;
            rot->x = r->x;
            rot->y = r->y;
            rot->z = r->z;
        }
        if( rot->time < f->t )
            rot->time = this->highest_frame;

        c = (unsigned int)j->translate_frames.size();
        for( i = 0; i < c; i++ )
        {
            r = &j->translate_frames[ i ];
            if( r->time < f->t )
                continue;
            if( r->time > trans->time )
                continue;
            trans->time = r->time;
            trans->x = r->x;
            trans->y = r->y;
            trans->z = r->z;
        }
        if( trans->time < f->t )
            trans->time = this->highest_frame;
    }

};
