#include <mutex>
#include <algorithm>
#include <string>
#include <iostream>
#include <vector>

#include "WareHouse_DB.hpp"
#include "Box.hpp"

void WareHouse_DB::stock_box(Box box) {
    storage_.push_back(box);
}

bool WareHouse_DB::find_box(unsigned int id, Box &box) {
    std::_List_const_iterator<Box> ptr = std::find_if(storage_.cbegin(), storage_.cend(),
            [&] (Box tmp) {return (tmp.get_id() == id); });
    if (ptr == storage_.cend()) {
        std::unique_lock<std::mutex> cout_mtx;
        std::cerr << "Box does not exist\n";
        return false;
    }
    else {
        box = *ptr;
        return true;
    }
}

std::string WareHouse_DB::get_str_info_box(Box box) {
    std::string str;
    str.append("id: " + std::to_string(box.get_id()) + "\n");
    str.append("items: \n");
    str.append(box.get_str_items());

    return str;
}

void WareHouse_DB::print_all_boxes() {
    std::list<Box>::iterator ptr;

    for (ptr = storage_.begin(); ptr != storage_.end(); ptr++) {
        std::cout << ptr->get_id() << ": ";
        std::cout << ptr->get_str_items() << std::endl;
    }
}