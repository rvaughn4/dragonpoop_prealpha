
#ifndef dragonpoop_model_component_tree_byownertype_h
#define dragonpoop_model_component_tree_byownertype_h

#include "../../../core/bytetree/multibytetree.h"
#include "model_component_tree_byidtype.h"
#include <stdint.h>

namespace dragonpoop
{

    class model_component_tree_byownertype : public multibytetree
    {
    private:

    protected:

        //ovverride to handle deleteion of leaf
        virtual void onRemoveLeaf( void *o );
        //ovverride to generate branches
        virtual multibytetree *genBranch( void );

    public:

        //ctor
        model_component_tree_byownertype( void );
        //dtor
        virtual ~model_component_tree_byownertype( void );
        //find leaf
        void findLeaves( dpid id, uint16_t ctype, std::list<model_component *> *l );
        //find leaves by two owners
        void findLeaves( dpid id0, dpid id1, uint16_t ctype, std::list<model_component *> *l );
        //find leaves by three owners
        void findLeaves( dpid id0, dpid id1, dpid id2, uint16_t ctype, std::list<model_component *> *l );
        //add leaf
        void addLeaf( dpid id, uint16_t ctype, model_component *o );
        //remove leaf
        void removeLeaf( model_component *o );
        
    };
    
};

#endif