
#ifndef dragonpoop_model_component_tree_byowner_h
#define dragonpoop_model_component_tree_byowner_h

#include "../../../core/bytetree/dpid_multibytetree.h"

namespace dragonpoop
{

    class model_component;

    class model_component_tree_byowner : public dpid_multibytetree
    {
    private:

    protected:

        //ovverride to handle deleteion of leaf
        virtual void onRemoveLeaf( void *o );
        //ovverride to generate branches
        virtual multibytetree *genBranch( void );

    public:

        //ctor
        model_component_tree_byowner( void );
        //dtor
        virtual ~model_component_tree_byowner( void );
        //find leaf
        void findLeaves( dpid id, std::list<model_component *> *l );
        //find leaves by two owners
        void findLeaves( dpid id0, dpid id1, std::list<model_component *> *l );
        //find leaves by three owners
        void findLeaves( dpid id0, dpid id1, dpid id2, std::list<model_component *> *l );
        //add leaf
        void addLeaf( dpid id, model_component *o );
        //remove leaf
        void removeLeaf( model_component *o );
        
    };
    
};

#endif