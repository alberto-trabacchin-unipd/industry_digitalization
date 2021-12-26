#include <string>
#include <algorithm>
#include "Box.hpp"

Box::Box(unsigned int id)
        : id_(id), avail_cap_(10) {}

void Box::put_item(Item item) {
    items_.push_back(item);
    avail_cap_--;
}

std::string Box::get_str_items() {
    std::string str_items;
    std::for_each(items_.cbegin(), items_.cend(),
            [&str_items](Item item) { str_items.append(item.get_name() + " "); });
    
    return str_items;
}