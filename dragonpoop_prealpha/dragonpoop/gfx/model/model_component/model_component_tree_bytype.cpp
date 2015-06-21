
#include "model_component_tree_bytype.h"
#include "model_component.h"

namespace dragonpoop
{

    //ctor
    model_component_tree_bytype::model_component_tree_bytype( void ) : multibytetree()
    {

    }

    //dtor
    model_component_tree_bytype::~model_component_tree_bytype( void )
    {
        this->clear();
    }

    //find leaf
    void model_component_tree_bytype::findLeaves( uint16_t ctype, std::list<model_component *> *l )
    {
        this->multibytetree::findLeaves( (char *)&ctype, sizeof( uint16_t ), (std::list<void *> *)l );
    }

    //add leaf
    void model_component_tree_bytype::addLeaf( uint16_t ctype, model_component *o )
    {
        this->multibytetree::addLeaf( (char *)&ctype, sizeof( uint16_t ), (void *)o );
    }

    //remove leaf
    void model_component_tree_bytype::removeLeaf( model_component *o )
    {
        this->multibytetree::removeLeaf( (void *)o );
    }

    //ovverride to handle deleteion of leaf
    void model_component_tree_bytype::onRemoveLeaf( void *o )
    {

    }

    //ovverride to generate branches
    multibytetree *model_component_tree_bytype::genBranch( void )
    {
        return new model_component_tree_bytype();
    }
    
};
