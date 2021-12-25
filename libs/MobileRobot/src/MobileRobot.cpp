#include <mutex>
#include <iostream>
#include "MobileRobot.hpp"

void MobileRobot::thread_fun() {
    while(true) {
        pp.start_carry();
        box_ptr_ = pp.carry_box();
        pp.end_carry();
        {
        std::unique_lock<std::mutex> mtx_lck(cout_mtx);
        std::cout << "Recuperato pezzo\n";
        }

        //Drive to warehouse...
    }
}
