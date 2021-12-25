#include "Box.hpp"

Box::Box(unsigned int id)
        : id_(id), avail_cap_(10) {}

void Box::put_item(Item item) {
    items_.push_back(item);
    avail_cap_--;
}
