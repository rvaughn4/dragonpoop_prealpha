
#ifndef dragonpoop_ms3d_model_loader_h
#define dragonpoop_ms3d_model_loader_h

#include "../models.h"
#include "ms3d_model_header.h"
#include "ms3d_model_vertex.h"
#include "ms3d_model_triangle.h"
#include "ms3d_model_group.h"
#include "ms3d_model_material.h"
#include "ms3d_model_animation.h"
#include "ms3d_model_joint.h"
#include <fstream>
#include <vector>
#include "../../dpvertex/dpvertexes.h"

namespace dragonpoop
{

    class ms3d_model_loader
    {

    private:

        model_writelock *m;
        dpthread_lock *thd;

        //vertexes
        std::vector<ms3d_model_vertex_m> verts;
        //triangles
        std::vector<ms3d_model_triangle_m> tris;
        //groups
        std::vector<ms3d_model_group_m> groups;
        //materials
        std::vector<ms3d_model_material_m> mats;
        //animation
        ms3d_model_animation_section anim;
        //joints
        std::vector<ms3d_model_joint_m> joints;

    protected:

        //ctor
        ms3d_model_loader( model_writelock *ml, dpthread_lock *thd );
        //dtor
        virtual ~ms3d_model_loader( void );
        //load file header
        bool readHeader( std::fstream *f );
        //save file header
        bool writeHeader( std::fstream *f );
        //load vertex section
        bool readVertexSection( std::fstream *f );
        //save vertex section
        bool writeVertexSection( std::fstream *f );
        //load vertex
        bool readVertex( std::fstream *f );
        //save vertex
        bool writeVertex( std::fstream *f, ms3d_model_vertex_m *h );
        //load triangle section
        bool readTriangleSection( std::fstream *f );
        //save triangle section
        bool writeTriangleSection( std::fstream *f );
        //load triangle
        bool readTriangle( std::fstream *f );
        //save triangle
        bool writeTriangle( std::fstream *f, ms3d_model_triangle_m *h );
        //load group section
        bool readGroupSection( std::fstream *f );
        //save group section
        bool writeGroupSection( std::fstream *f );
        //load group
        bool readGroup( std::fstream *f );
        //save group
        bool writeGroup( std::fstream *f, ms3d_model_group_m *h );
        //load group triangle
        bool readGroupTriangle( std::fstream *f, ms3d_model_group_m *h );
        //save group triangle
        bool writeGroupTriangle( std::fstream *f, ms3d_model_group_triangle *h );
        //load materials
        bool readMaterialSection( std::fstream *f );
        //save materials
        bool writeMaterialSection( std::fstream *f );
        //load material
        bool readMaterial( std::fstream *f );
        //save material
        bool writeMaterial( std::fstream *f, ms3d_model_material_m *h );
        //load animation section
        bool readAnimationSection( std::fstream *f );
        //save animation section
        bool writeAnimationSection( std::fstream *f );
        //load joint section
        bool readJointSection( std::fstream *f );
        //save joint section
        bool writeJointSection( std::fstream *f );
        //load joint
        bool readJoint( std::fstream *f );
        //save joint
        bool writeJoint( std::fstream *f, ms3d_model_joint_m *h );
        //load joint keyframe
        bool readJointKeyframe( std::fstream *f, std::vector<ms3d_model_joint_keyframe> *l );
        //save joint keyframe
        bool writeJointKeyframe( std::fstream *f, ms3d_model_joint_keyframe *h );

        //joints

        //create vertexes
        void createVertexes( void );
        //convert vertexes for saving
        void convertVertexes( void );
        //create groups
        void createGroups( void );
        //convert groups
        void convertGroups( void );
        //convert group triangles
        void convertGroupTriangles( void );
        //convert group triangles
        void convertGroupTriangles( unsigned int gi, ms3d_model_group_m *g );
        //find group containing triangle
        ms3d_model_group_m *findGroupHavingTriangle( unsigned int ti );
        //create triangles
        void createTriangles( void );
        //convert triangles
        void convertTriangles( void );
        //create triangle vertexes
        void createTriangleVertexes( ms3d_model_triangle_m *t );
        //convert triangle vertexes
        void convertTriangleVertexes( ms3d_model_triangle_m *t );
        //find offset for vertex by id
        unsigned int findVertex( dpid id );
        //create triangle vertex
        void createTriangleVertex( ms3d_model_triangle_m *t, ms3d_model_vertex_m *v, dpxyzw *n, dpst *t0, dpst *t1 );
        //convert triangle vertex
        void convertTriangleVertex( ms3d_model_triangle_m *t, unsigned int vi, model_triangle_vertex_ref *v );

    public:

        //load file
        static bool load( dpthread_lock *thd, model_writelock *ml, const char *fname );
        //save file
        static bool save( dpthread_lock *thd, model_writelock *ml, const char *fname );
    };
    
};

#endif