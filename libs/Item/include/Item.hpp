#ifndef ITEM_HPP
#define ITEM_HPP

/*
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
    unsigned int get_min() { return pick_min_; };
    void set_sec(unsigned int sec) { pick_sec_ = sec; };
    void increment_min(unsigned int plus_min) { pick_min_ += plus_min; };
    void increment_sec(unsigned int plus_sec) { pick_sec_ += plus_sec; };
    void print();
    std::string get_str_time();
    double get_pos() { return position_; };

private:
    unsigned int pick_min_;
    unsigned int pick_sec_;
    std::string name_;
    double position_;
};*/


#include <string>

class Item {

public:
    Item(std::string name, unsigned int MM, unsigned int SS, double position);
    Item() : Item("0", 0, 0, 0) {}

    std::string get_name() { return name_; };
    unsigned int get_MM() { return MM_; };
    unsigned int get_SS() { return SS_; };
    void set_MM(unsigned int MM) { MM_ = MM; };
    void set_SS(unsigned int SS) { SS_ = SS; };
    double get_pos() { return position_; };
    std::string get_str_time();


private:
    std::string name_;
    unsigned int MM_;
    unsigned int SS_;
    double position_;

};


#endif