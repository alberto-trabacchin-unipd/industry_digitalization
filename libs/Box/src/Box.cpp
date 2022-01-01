#include <string>
#include <algorithm>
#include "Box.hpp"

Box::Box(const size_t id)
        : id_(id), avail_cap_(BOX_CAPACITY) {}

void Box::place_item(const Item &item) {
    items_.push_back(item);
    avail_cap_--;
}

std::string Box::get_str_items() {
    std::string str;
    std::for_each(items_.cbegin(), items_.cend(),
                  [&](Item item) { str.append(item.get_name() + " ");});
    return str;
}

std::string Box::get_str_time_items() {
    std::string str;
    std::for_each(items_.cbegin(), items_.cend(), [&](Item item) {
        str.append("\t" + item.get_name() + " -> " + item.get_str_time() + "\n");
    });
    
    return str;
}