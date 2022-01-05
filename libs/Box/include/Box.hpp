#ifndef BOX_HPP
#define BOX_HPP

#include <vector>
#include <string>
#include "Item.hpp"


class Box {

public:
    Box(const size_t id);

    bool is_full() { return avail_cap_ == 0; };
    size_t get_id() { return id_; };
    void place_item(const Item &item);
    std::string get_str_items();
    std::string get_str_time_items();

private:
    unsigned int id_;
    unsigned int avail_cap_;
    std::vector<Item> items_;

};

#endif