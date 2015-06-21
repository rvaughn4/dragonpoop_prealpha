
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
