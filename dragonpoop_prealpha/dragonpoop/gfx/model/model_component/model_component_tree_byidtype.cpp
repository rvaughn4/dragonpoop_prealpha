
#include "model_component_tree_byidtype.h"
#include "model_component.h"

namespace dragonpoop
{

    //ctor
    model_component_tree_byidtype::model_component_tree_byidtype( void ) : bytetree()
    {

    }

    //dtor
    model_component_tree_byidtype::~model_component_tree_byidtype( void )
    {
        this->clear();
    }

    //find leaf
    model_component *model_component_tree_byidtype::findLeaf( dpid id, uint16_t ctype )
    {
        dpidtype t;
        t.id = id;
        t.ctype = ctype;
        return (model_component *)this->bytetree::findLeaf( (char *)&t, sizeof( t ) );
    }

    //add leaf
    void model_component_tree_byidtype::addLeaf( dpid id, uint16_t ctype, model_component *o )
    {
        dpidtype t;
        t.id = id;
        t.ctype = ctype;
        this->bytetree::addLeaf( (char *)&t, sizeof( t ), (void *)o );
    }

    //remove leaf
    void model_component_tree_byidtype::removeLeaf( model_component *o )
    {
        this->bytetree::removeLeaf( (void *)o );
    }

    //ovverride to handle deleteion of leaf
    void model_component_tree_byidtype::onRemoveLeaf( void *o )
    {

    }

    //ovverride to generate branches
    bytetree *model_component_tree_byidtype::genBranch( void )
    {
        return new model_component_tree_byidtype();
    }
    
};
