
#include "model_component_tree_byowner.h"

namespace dragonpoop
{

    //ctor
    model_component_tree_byowner::model_component_tree_byowner( void ) : dpid_multibytetree()
    {

    }

    //dtor
    model_component_tree_byowner::~model_component_tree_byowner( void )
    {

    }

    //find leaf
    void model_component_tree_byowner::findLeaves( dpid id, std::list<model_component *> *l )
    {
        this->dpid_multibytetree::findLeaves( id, (std::list<void *> *)l );
    }

    //find leaves by two owners
    void model_component_tree_byowner::findLeaves( dpid id0, dpid id1, std::list<model_component *> *l )
    {
        std::list<model_component *> l0, l1;
        std::list<model_component *>::iterator i0, i1;
        model_component *p0, *p1;
        bool b;

        this->findLeaves( id0, &l0 );
        this->findLeaves( id1, &l1 );

        for( i0 = l0.begin(); i0 != l0.end(); ++i0 )
        {
            p0 = *i0;
            b = 0;
            for( i1 = l1.begin(); i1 != l1.end() && !b; ++i1 )
            {
                p1 = *i1;
                if( p1 == p0 )
                    b = 1;
            }
            if( b )
                l->push_back( p0 );
        }
    }

    //find leaves by three owners
    void model_component_tree_byowner::findLeaves( dpid id0, dpid id1, dpid id2, std::list<model_component *> *l )
    {
        std::list<model_component *> l0, l1, l2;
        std::list<model_component *>::iterator i0, i1, i2;
        model_component *p0, *p1;
        bool b;

        this->findLeaves( id0, &l0 );
        this->findLeaves( id1, &l1 );
        this->findLeaves( id2, &l2 );

        for( i0 = l0.begin(); i0 != l0.end(); ++i0 )
        {
            p0 = *i0;
            b = 0;
            for( i1 = l1.begin(); i1 != l1.end() && !b; ++i1 )
            {
                p1 = *i1;
                if( p1 == p0 )
                    b = 1;
            }
            if( !b )
                continue;
            b = 0;
            for( i2 = l2.begin(); i2 != l2.end() && !b; ++i2 )
            {
                p1 = *i2;
                if( p1 == p0 )
                    b = 1;
            }
            if( b )
                l->push_back( p0 );
        }
    }

    //add leaf
    void model_component_tree_byowner::addLeaf( dpid id, model_component *o )
    {
        this->dpid_multibytetree::addLeaf( id, (void *)o );
    }

    //remove leaf
    void model_component_tree_byowner::removeLeaf( model_component *o )
    {
        this->dpid_multibytetree::removeLeaf( (void *)o );
    }

    //ovverride to handle deleteion of leaf
    void model_component_tree_byowner::onRemoveLeaf( void *o )
    {

    }

    //ovverride to generate branches
     multibytetree *model_component_tree_byowner::genBranch( void )
    {
        return new model_component_tree_byowner();
    }

};
