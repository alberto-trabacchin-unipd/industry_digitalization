#ifndef BOX_HPP
#define BOX_HPP

#include <vector>
#include "Item.hpp"


class Box {

public:
    Box(unsigned int id);
    void put_item(Item item);
    bool is_full() { return avail_cap_ == 0; };

private:
    unsigned int id_;
    std::vector<Item> items_;
    unsigned int avail_cap_;

};

#endif