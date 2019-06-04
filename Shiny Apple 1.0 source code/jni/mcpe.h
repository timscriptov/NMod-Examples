#pragma once
#include <string>
#include <vector>

class Block {
    public:
    static Block* mGoldBlock;
};

class Item {
    public:
    static Item* mApple;
    static Item* mApple_enchanted;
};

class ItemInstance {
    public:
    ItemInstance(const Item&, int);
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