
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
