#ifndef BOX_HPP
#define BOX_HPP

#define BOX_CAPACITY 10
/*
#include <vector>
#include "Item.hpp"


class Box {

public:
    Box(unsigned int id);
    void put_item(Item item);
    bool is_full() { return avail_cap_ == 0; };
    void set_id(unsigned int id) { id_ = id; };
    unsigned int get_id() { return id_; };
    std::vector<Item> get_items() { return items_; };
    std::string get_str_items();

private:
    unsigned int id_;
    std::vector<Item> items_;
    unsigned int avail_cap_;

};
*/

#include <vector>
#include <string>
#include "Item.hpp"

class Box {

public:
    Box(size_t id);

    bool is_full() { return avail_cap_ == 0; };
    size_t get_id() { return id_; };
    void place_item(Item &item);
    std::string get_str_items();

private:
    unsigned int id_;
    unsigned int avail_cap_;
    std::vector<Item> items_;

};

#endif