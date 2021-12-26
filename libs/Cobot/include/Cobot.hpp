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
    Cobot(double conveyor_len, double conveyor_vel, MVSystem &mvs, unsigned int id);
    Cobot(std::string conveyor_len, std::string conveyor_vel, MVSystem &mvs, unsigned int id)
            : Cobot(std::stod(conveyor_len), std::stod(conveyor_vel), mvs, id) {}

    void print_message(Item item, unsigned int id);
    void thread_fun();
    void set_pick_time(Item &item, unsigned int minutes, unsigned int seconds);

private:
    double conveyor_vel_;
    double conveyor_len_;
    unsigned int pick_count;
    unsigned int id_;
    RW *rw;

};

#endif