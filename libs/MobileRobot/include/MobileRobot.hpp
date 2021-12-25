#ifndef MOBILEROBOT_HPP
#define MOBILEROBOT_HPP

#include <memory>
#include "Box.hpp"
#include "PickPlace.hpp"

extern PickPlace pp;
extern std::mutex cout_mtx;


class MobileRobot {

public:
    void thread_fun();

private:
    std::shared_ptr<Box> box_ptr_;

};

#endif