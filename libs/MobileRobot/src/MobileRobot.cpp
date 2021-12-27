#include <mutex>
#include <iostream>

#include "MobileRobot.hpp"
#include "WareHouse_DB.hpp"


void MobileRobot::thread_fun() {
    bool all_cobots_off = false;
    while(!(shutdown && all_cobots_off)) {
        pp.start_carry();
        //box_ptr_ = pp.carry_box();
        mob_robot_box = pp.carry_box();
        pp.end_carry();

        all_cobots_off = pp.check_cobots_status();

        //Drive to warehouse...

        whdb.stock_box(mob_robot_box);
        MobileRobot::print_message();
    }

    std::cout << "Robot mobile spento\n";
}

void MobileRobot::print_message() {
    std::unique_lock<std::mutex> mtx_lck(cout_mtx);
    std::cout << "Robot mobile: recuperato la scatola " << mob_robot_box.get_id();
    std::cout << " e portata in magazzino\n";
}