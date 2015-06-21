
#ifndef dragonpoop_model_component_tree_byid_h
#define dragonpoop_model_component_tree_byid_h

#include "../../../core/bytetree/dpid_bytetree.h"

namespace dragonpoop
{

    class model_component;
    
    class model_component_tree_byid : public dpid_bytetree
    {
    private:

    protected:

        //ovverride to handle deleteion of leaf
        virtual void onRemoveLeaf( void *o );
        //ovverride to generate branches
        virtual bytetree *genBranch( void );

    public:

        //ctor
        model_component_tree_byid( void );
        //dtor
        virtual ~model_component_tree_byid( void );
        //find leaf
        model_component *findLeaf( dpid id );
        //add leaf
        void addLeaf( dpid id, model_component *o );
        //remove leaf
        void removeLeaf( model_component *o );

    };
    
};

#endif