#ifndef ITEM_HPP
#define ITEM_HPP

#include <string>
#include <vector>

class Item {

public:
    Item(unsigned int pick_min, unsigned int pick_sec, std::string name, double position);

    std::string get_name() { return name_; };
    std::vector<std::string> get_time();
    void print();

private:
    unsigned int pick_min_;
    unsigned int pick_sec_;
    std::string name_;
    double position_;
};

#endif