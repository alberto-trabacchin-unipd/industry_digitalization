#ifndef ITEM_HPP
#define ITEM_HPP

#include <string>


class Item {

public:
    Item(const std::string name, const unsigned int MM, const unsigned int SS, const double position);
    Item() : Item("0", 0, 0, 0) {}

    std::string get_name() { return name_; };
    unsigned int get_MM() { return MM_; };
    unsigned int get_SS() { return SS_; };
    void set_MM(const unsigned int MM) { MM_ = MM; };
    void set_SS(const unsigned int SS) { SS_ = SS; };
    double get_pos() { return position_; };
    std::string get_str_time();


private:
    std::string name_;
    unsigned int MM_;
    unsigned int SS_;
    double position_;

};

#endif