#ifndef MOBILEROBOT_HPP
#define MOBILEROBOT_HPP

#include <memory>
#include "Box.hpp"
#include "PickPlace.hpp"
#include "WareHouse_DB.hpp"

extern PickPlace pp;
extern std::mutex cout_mtx;
extern WareHouse_DB whdb;


class MobileRobot {

public:
    MobileRobot() : mob_robot_box(Box{1}) {}
    void thread_fun();
    void print_message();

private:
    //std::shared_ptr<Box> box_ptr_;
    Box mob_robot_box;

};

#endif