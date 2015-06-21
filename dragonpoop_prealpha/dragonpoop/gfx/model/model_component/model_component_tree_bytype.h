
#ifndef dragonpoop_model_component_tree_bytype_h
#define dragonpoop_model_component_tree_bytype_h

#include "../../../core/bytetree/multibytetree.h"
#include <stdint.h>

namespace dragonpoop
{

    class model_component;

    class model_component_tree_bytype : public multibytetree
    {
    private:

    protected:

        //ovverride to handle deleteion of leaf
        virtual void onRemoveLeaf( void *o );
        //ovverride to generate branches
        virtual multibytetree *genBranch( void );

    public:

        //ctor
        model_component_tree_bytype( void );
        //dtor
        virtual ~model_component_tree_bytype( void );
        //find leaf
        void findLeaves( uint16_t ctype, std::list<model_component *> *l );
        //add leaf
        void addLeaf( uint16_t ctype, model_component *o );
        //remove leaf
        void removeLeaf( model_component *o );
        
    };
    
};

#endif