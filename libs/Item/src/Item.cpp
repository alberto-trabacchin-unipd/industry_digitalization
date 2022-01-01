#include "Item.hpp"

Item::Item(const std::string name, const unsigned int MM, const unsigned int SS, const double position)
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