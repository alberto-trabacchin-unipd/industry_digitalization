#ifndef ITEM_HPP
#define ITEM_HPP

#include <string>
#include <vector>
#include <mutex>

extern std::mutex cout_mtx;


class Item {

public:
    Item(unsigned int pick_min, unsigned int pick_sec, std::string name, double position);

    std::string get_name() { return name_; };
    std::vector<std::string> get_time();
    unsigned int get_sec() { return pick_sec_; };
    void set_sec(unsigned int sec) { pick_sec_ = sec; };
    void increment_min(unsigned int plus_min) { pick_min_ += plus_min; };
    void increment_sec(unsigned int plus_sec) { pick_sec_ += plus_sec; };
    void print();
    std::string get_str_time();

private:
    unsigned int pick_min_;
    unsigned int pick_sec_;
    std::string name_;
    double position_;
};

#endif