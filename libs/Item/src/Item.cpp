#include <string>
#include <vector>
#include <iostream>

#include "Item.hpp"


Item::Item(unsigned int pick_min, unsigned int pick_sec, std::string name, double position)
        : pick_min_(pick_min), pick_sec_(pick_sec), name_(name), position_(position) {}


std::vector<std::string> Item::get_time() {
    std::vector<std::string> v_times;
    v_times.push_back(std::to_string(pick_min_));
    v_times.push_back(std::to_string(pick_sec_));
    
    return v_times;
}

void Item::print() {
    std::cout << "name: " << name_ << std::endl;
    std::cout << "mm: " << pick_min_ << std::endl;
    std::cout << "ss: " << pick_sec_ << std::endl;
    std::cout << "position: " << position_ << std::endl;
}