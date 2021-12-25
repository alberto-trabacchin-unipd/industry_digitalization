#ifndef COBOT_HPP
#define COBOT_HPP

#include <mutex>
#include <string>

#include "RW.hpp"
#include "MVSystem.hpp"
#include "Item.hpp"

extern std::mutex cout_mtx;


class Cobot {

public:
    Cobot(double conveyor_vel, double conveyor_len, MVSystem* mvs, std::string id);

    void print_message(Item* item);
    void thread_fun();
    void calc_pick_time(Item* item);

private:
    double conveyor_vel_;
    double conveyor_len_;
    unsigned int pick_count;
    std::string id_;
    RW *rw;

    void add_time(unsigned int pick_time, Item* item);

};

#endif