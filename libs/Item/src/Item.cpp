/*#include <string>
#include <vector>
#include <iostream>
#include <mutex>

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

std::string Item::get_str_time() {
    std::string str_min{std::to_string(pick_min_)};
    if (pick_min_ < 10)
        str_min = "0" + str_min;
    std::string str_sec{std::to_string(pick_sec_)};
    if (pick_sec_ < 10)
        str_sec = "0" + str_sec;
    return (str_min + ":" + str_sec);
}*/


#include "Item.hpp"

Item::Item(std::string name, unsigned int MM, unsigned int SS, double position)
        : name_(name), MM_(MM), SS_(SS), position_(position) {}

std::string Item::get_str_time() {
    std::string str_min{std::to_string(MM_)};
    if (MM_ < 10)
        str_min = "0" + str_min;
    std::string str_sec{std::to_string(SS_)};
    if (SS_ < 10)
        str_sec = "0" + str_sec;
    return (str_min + ":" + str_sec);
}