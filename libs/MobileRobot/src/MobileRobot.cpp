#include <mutex>
#include <iostream>

#include "MobileRobot.hpp"
#include "WareHouse_DB.hpp"


void MobileRobot::thread_fun() {
    while(true) {
        pp.start_carry();
        box_ptr_ = pp.carry_box();
        pp.end_carry();
        {
        std::unique_lock<std::mutex> mtx_lck(cout_mtx);
        std::cout << "Recuperata scatola\n";
        }

        //Drive to warehouse...

        whdb.stock_box(*box_ptr_);
        {
        std::unique_lock<std::mutex> mtx_lck(cout_mtx);
        std::cout << "Stoccata scatola n. " << box_ptr_->get_id() << std::endl;
        }
    }
}
