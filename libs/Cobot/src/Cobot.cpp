#include <iostream>
#include <mutex>
#include <string>

#include "Cobot.hpp"
#include "RW.hpp"
#include "PickPlace.hpp"
#include "MVSystem.hpp"
#include "Item.hpp"

PickPlace pp;


Cobot::Cobot(double conveyor_vel, double conveyor_len, MVSystem* mvs, std::string id) {
    if (conveyor_vel <= 0 || conveyor_len <= 0) {
        std::cerr << "ERR: conveyor parameters not valid!\n";
        exit(EXIT_FAILURE);
    }
    conveyor_vel_ = conveyor_vel;
    conveyor_len_ = conveyor_len;
    id_ = id;
    rw = &mvs->rw;
    pick_count = 0;
}

void Cobot::print_message(Item* item) {
    std::unique_lock<std::mutex> mtx_lck(cout_mtx);
    std::cout << "(" << pick_count << ") ";
    std::cout << "Cobot " << id_;
    std::cout << ": prelevato pezzo " << item->get_name();
    std::cout << " al tempo " << item->get_str_time() << std::endl;
}

void Cobot::calc_pick_time(Item* item) {
    double pick_time = conveyor_len_ / conveyor_vel_;
    Cobot::add_time(pick_time, item);
}

void Cobot::add_time(unsigned int pick_time, Item* item) {
    unsigned int minutes = pick_time / 60;
    unsigned int seconds = pick_time % 60;

    if ((item->get_sec() + seconds) > 59) {
        item->increment_min(1);
        seconds = seconds - (60 - item->get_sec());
        item->set_sec(seconds);
    }
    else
        item->increment_sec(seconds);
    
    item->increment_min(minutes);
}

void Cobot::thread_fun() {
    while (true) {
        rw->start_read();
        Item tmp_item = rw->pop_data();
        rw->end_read();
        calc_pick_time(&tmp_item);
        pick_count++;
        print_message(&tmp_item);
    }
}