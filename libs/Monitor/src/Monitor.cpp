#include <mutex>
#include <condition_variable>
#include <iostream>
#include <algorithm>
#include <iomanip>

#include "Monitor.hpp"
#include "Box.hpp"


Monitor::Monitor() : item_data_(n_cobots), canUseData_(n_cobots), data_ready_(n_cobots, false),
                     cobots_box_(Box{1}), placing_(n_cobots, false), mobile_box_(Box{1}), n_boxes_(1)  {}


void Monitor::start_write(size_t i) {
    std::unique_lock<std::mutex> mtx_lck(mutex_data_);
    canUseData_.at(i).wait(mtx_lck, [&]{ return data_ready_.at(i) == false; });
}

void Monitor::end_write(size_t i) {
    std::unique_lock<std::mutex> mtx_lck(mutex_data_);
    data_ready_.at(i) = true;
    canUseData_.at(i).notify_one();
}

void Monitor::start_read(size_t i) {
    std::unique_lock<std::mutex> mtx_lck(mutex_data_);
    canUseData_.at(i).wait(mtx_lck, [&]{ return data_ready_.at(i) == true; });
}

void Monitor::end_read(size_t i) {
    std::unique_lock<std::mutex> mtx_lck(mutex_data_);
    data_ready_.at(i) = false;
    canUseData_.at(i).notify_one();
}

void Monitor::start_place(size_t i) {
    std::unique_lock<std::mutex> mtx_lck(mutex_box_);
  
    while (cobots_box_.is_full() || !std::all_of(placing_.cbegin(), placing_.cend(),
                                            [](bool placing){ return placing == false; })) {
        canPlace.wait(mtx_lck);
    }
    placing_.at(i) = true;
}

void Monitor::place_item(Item &item) {
    cobots_box_.place_item(item);
}

void Monitor::end_place(size_t i) {
    std::unique_lock<std::mutex> mtx_lck(mutex_box_);
    placing_.at(i) = false;
    if (cobots_box_.is_full())
        canCarry.notify_all();
    else
        canPlace.notify_all();
}

void Monitor::start_carry() {
    std::unique_lock<std::mutex> mtx_lck(mutex_box_);
    canCarry.wait(mtx_lck, [&]{ return cobots_box_.is_full(); });
}

void Monitor::end_carry() {
    std::unique_lock<std::mutex> mtx_lck(mutex_box_);
    cobots_box_ = Box{++n_boxes_};
}

void Monitor::print_cobot_message(size_t i, Item &item, size_t n_box) {
    std::string str {"abcdefghijklmnopqrstuvwxyz"};
    std::unique_lock<std::mutex> cout_lck(cout_mutex_);
    
    std::cout << "Cobot linea di trasporto " << str.at(i) << ": ";
    std::cout << "recuperato componente di tipo " << item.get_name();
    std::cout << " al tempo " << item.get_str_time();
    std::cout << std::fixed;
    std::cout << " in posizione " << std::setprecision(2) << item.get_pos();
    std::cout << " e inserito nella scatola " << n_box << std::endl;
}

void Monitor::print_mob_robot_message(size_t n_box) {
    std::unique_lock<std::mutex> cout_lck(cout_mutex_);
    std::cout << "Robot mobile: Recuperato la scatola " << n_box;
    std::cout << " e portata in magazzino\n";
}

bool Monitor::find_box(unsigned int id, Box &box) {
    std::_List_const_iterator<Box> ptr = std::find_if(storage_.cbegin(), storage_.cend(),
            [&] (Box tmp) {return (tmp.get_id() == id); });
    if (ptr == storage_.cend()) {
        std::unique_lock<std::mutex> cout_mtx;
        std::cerr << "Box " << id << " does not exist\n";
        return false;
    }
    else {
        box = *ptr;
        return true;
    }
}