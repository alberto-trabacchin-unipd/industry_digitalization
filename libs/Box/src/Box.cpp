#include <string>
#include <algorithm>
#include "Box.hpp"

Box::Box(size_t id)
        : id_(id), avail_cap_(BOX_CAPACITY) {}

void Box::place_item(Item &item) {
    items_.push_back(item);
    avail_cap_--;
}

std::string Box::get_str_items() {
    std::string str;
    std::for_each(items_.cbegin(), items_.cend(),
                  [&](Item item) { str.append(item.get_name() + " ");});
    return str;
}