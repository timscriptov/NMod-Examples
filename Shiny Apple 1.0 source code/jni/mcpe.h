#pragma once
#include <string>
#include <vector>

class Block {
    public:
    static Block* mNewGoldBlock;
};

class VanillaItem {
    public:
    static Item* mNewApple;
    static Item* mNewApple_enchanted;
};

class ItemInstance {
    public:
    ItemInstance(const VanillaItem&, int);
};

class Recipes {
    public:
    class Type {
        public:
        char filler[4];
    };
    int init();
    void addShapedRecipe(
        ItemInstance const&, 
        std::string const&, 
        std::string const&, 
        std::string const&, 
        std::vector<Recipes::Type, std::allocator<Recipes::Type>> const&
        );
};

template <class A, class B> 
std::vector<Recipes::Type, std::allocator<Recipes::Type>> 
definition(char, A, char, B);
