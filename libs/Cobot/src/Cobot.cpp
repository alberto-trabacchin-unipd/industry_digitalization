#include <iostream>
#include <mutex>
#include <iomanip>
#include <string>
#include <thread>
#include <chrono>

#include "Cobot.hpp"
#include "RW.hpp"
#include "PickPlace.hpp"
#include "MVSystem.hpp"
#include "Item.hpp"

PickPlace pp;


Cobot::Cobot(double conveyor_len, double conveyor_vel, MVSystem &mvs, unsigned int id) {
    if (conveyor_vel <= 0 || conveyor_len <= 0) {
        std::cerr << "ERR: conveyor parameters not valid!\n";
        exit(EXIT_FAILURE);
    }
    conveyor_vel_ = conveyor_vel;
    conveyor_len_ = conveyor_len;
    id_ = id;
    rw = &mvs.rw;
    pick_count = 0;
}

void Cobot::print_message(Item item, unsigned int box_id) {
    std::unique_lock<std::mutex> mtx_lck(cout_mtx);
    std::cout << "(" << pick_count << ")\t";

    if (id_ == 1)
        std::cout << "Cobot linea di trasporto a: ";
    else if (id_ == 2)
        std::cout << "Cobot linea di trasporto b: ";
    
    std::cout << "recuperato componente di tipo " << item.get_name();
    std::cout << " al tempo " << item.get_str_time();
    std::cout << std::fixed;
    std::cout << " in posizione " << std::setprecision(2) << item.get_pos();
    std::cout << " e inserito nella scatola " << box_id << std::endl;
}

void Cobot::set_pick_time(Item &item, unsigned int minutes, unsigned int seconds) {
    if ((item.get_sec() + seconds) > 59) {
        item.increment_min(1);
        seconds = seconds - (60 - item.get_sec());
        item.set_sec(seconds);
    }
    else
        item.increment_sec(seconds);
    
    item.increment_min(minutes);   
}

//time_read + delta_conv - time_now

void Cobot::thread_fun() {
    using std::chrono::steady_clock;
    using std::chrono::duration_cast;

    Item tmp_item{0,0,"0",0};
    unsigned int delta_sec = static_cast<unsigned int> (conveyor_len_ / conveyor_vel_);
    unsigned int minutes = delta_sec / 60;
    unsigned int seconds = delta_sec % 60;
    unsigned int box_id = 0;
    steady_clock::time_point time_begin = steady_clock::now();
    steady_clock::time_point time_end;
    unsigned int waiting_time;

    while (true) {
        rw->start_read();
        Item item = rw->pop_data();
        rw->end_read();
        time_end = steady_clock::now();
        int elaps_time =  static_cast<unsigned int>
                            (duration_cast<std::chrono::seconds>(time_end - time_begin).count());
        
        waiting_time = delta_sec + item.get_min()*60 + item.get_sec() - elaps_time;
        std::this_thread::sleep_for(std::chrono::seconds(waiting_time));
        set_pick_time(item, minutes, seconds);
        pick_count++;
        pp.start_put(id_-1);
        pp.put_item(item);
        box_id = pp.get_n_box();
        pp.end_put(id_-1);
        print_message(item, box_id);
    }
}