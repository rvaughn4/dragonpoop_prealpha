
#ifndef dragonpoop_model_component_tree_byidtype_h
#define dragonpoop_model_component_tree_byidtype_h

#include "../../../core/bytetree/dpid_bytetree.h"
#include <stdint.h>

namespace dragonpoop
{

    class model_component;

    struct dpidtype
    {
        dpid id;
        uint16_t ctype;
    };

    class model_component_tree_byidtype : public bytetree
    {
    private:

    protected:

        //ovverride to handle deleteion of leaf
        virtual void onRemoveLeaf( void *o );
        //ovverride to generate branches
        virtual bytetree *genBranch( void );

    public:

        //ctor
        model_component_tree_byidtype( void );
        //dtor
        virtual ~model_component_tree_byidtype( void );
        //find leaf
        model_component *findLeaf( dpid id, uint16_t ctype );
        //add leaf
        void addLeaf( dpid id, uint16_t ctype, model_component *o );
        //remove leaf
        void removeLeaf( model_component *o );
        
    };
    
};

#endif