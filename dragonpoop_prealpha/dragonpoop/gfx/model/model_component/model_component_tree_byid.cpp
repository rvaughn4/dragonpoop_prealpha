
#include "model_component_tree_byid.h"
#include "model_component.h"

namespace dragonpoop
{

    //ctor
    model_component_tree_byid::model_component_tree_byid( void ) : dpid_bytetree()
    {

    }

    //dtor
    model_component_tree_byid::~model_component_tree_byid( void )
    {
        this->clear();
    }

    //find leaf
    model_component *model_component_tree_byid::findLeaf( dpid id )
    {
        return (model_component *)this->dpid_bytetree::findLeaf( id );
    }

    //add leaf
    void model_component_tree_byid::addLeaf( dpid id, model_component *o )
    {
        this->dpid_bytetree::addLeaf( id, (void *)o );
    }

    //remove leaf
    void model_component_tree_byid::removeLeaf( model_component *o )
    {
        this->dpid_bytetree::removeLeaf( (void *)o );
    }

    //ovverride to handle deleteion of leaf
    void model_component_tree_byid::onRemoveLeaf( void *o )
    {

    }

    //ovverride to generate branches
    bytetree *model_component_tree_byid::genBranch( void )
    {
        return new model_component_tree_byid();
    }

};
