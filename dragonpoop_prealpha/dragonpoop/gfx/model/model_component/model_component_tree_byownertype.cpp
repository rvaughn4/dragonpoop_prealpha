
#include "model_component_tree_byownertype.h"

namespace dragonpoop
{

    //ctor
    model_component_tree_byownertype::model_component_tree_byownertype( void ) : multibytetree()
    {

    }

    //dtor
    model_component_tree_byownertype::~model_component_tree_byownertype( void )
    {

    }

    //find leaf
    void model_component_tree_byownertype::findLeaves( dpid id, uint16_t ctype, std::list<model_component *> *l )
    {
        dpidtype t;
        t.id = id;
        t.ctype = ctype;
        this->multibytetree::findLeaves( (char *)&t, sizeof( t ), (std::list<void *> *)l );
    }

    //find leaves by two owners
    void model_component_tree_byownertype::findLeaves( dpid id0, dpid id1, uint16_t ctype, std::list<model_component *> *l )
    {
        std::list<model_component *> l0, l1;
        std::list<model_component *>::iterator i0, i1;
        model_component *p0, *p1;
        bool b;

        this->findLeaves( id0, ctype, &l0 );
        this->findLeaves( id1, ctype, &l1 );

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

    //add leaf
    void model_component_tree_byownertype::addLeaf( dpid id, uint16_t ctype, model_component *o )
    {
        dpidtype t;
        t.id = id;
        t.ctype = ctype;
        this->multibytetree::addLeaf(  (char *)&t, sizeof( t ), (void *)o );
    }

    //remove leaf
    void model_component_tree_byownertype::removeLeaf( model_component *o )
    {
        this->multibytetree::removeLeaf( (void *)o );
    }

    //ovverride to handle deleteion of leaf
    void model_component_tree_byownertype::onRemoveLeaf( void *o )
    {

    }

    //ovverride to generate branches
    multibytetree *model_component_tree_byownertype::genBranch( void )
    {
        return new model_component_tree_byownertype();
    }
    
};
