#include <mutex>
#include <condition_variable>
#include <iostream>
#include <string>
#include <algorithm>
#include <iomanip>

#include "Monitor.hpp"
#include "Box.hpp"

bool shut_down = false;


Monitor::Monitor() : item_data_(n_cobots), canUseData_(n_cobots), data_ready_(n_cobots, false),
                     cobots_box_(Box{1}), n_box_count_(1) {}


void Monitor::write_data(size_t i, Item &item) {
    std::unique_lock<std::mutex> mtx_lck(mutex_data_);
    canUseData_.at(i).wait(mtx_lck, [&] { return data_ready_.at(i) == false; });
    item_data_.at(i) = item;
    data_ready_.at(i) = true;
    mtx_lck.unlock();
    canUseData_.at(i).notify_one();
}

Item Monitor::read_data(size_t i) {
    std::unique_lock<std::mutex> mtx_lck(mutex_data_);
    canUseData_.at(i).wait(mtx_lck, [&] { return data_ready_.at(i) == true; });
    Item item_red = item_data_.at(i);
    data_ready_.at(i) = false;
    mtx_lck.unlock();
    canUseData_.at(i).notify_one();
    return item_red;
}

void Monitor::place_item(Item &item) {
    std::unique_lock<std::mutex> mtx_lck(mutex_box_);
    canPlace.wait(mtx_lck, [&] { return !cobots_box_.is_full(); });
    cobots_box_.place_item(item);
    mtx_lck.unlock();

    if (cobots_box_.is_full())
        canCarry.notify_one();
    else
        canPlace.notify_one();
}

Box Monitor::carry_box() {
    std::unique_lock<std::mutex> mtx_lck(mutex_box_);
    canCarry.wait(mtx_lck, [&]{ return cobots_box_.is_full(); });
    Box mob_box = cobots_box_;
    std::unique_lock<std::mutex> mtx_count_lck(mutex_box_count_);
    cobots_box_ = Box{ ++n_box_count_ };
    mtx_count_lck.unlock();
    mtx_lck.unlock();
    canPlace.notify_one();
    return mob_box;
}


void Monitor::print_cobot_message(size_t i, Item &item) {
    std::string str {"abcdefghijklmnopqrstuvwxyz"};
    std::unique_lock<std::mutex> cout_lck(cout_mutex_);
    
    std::cout << "Cobot linea di trasporto " << str.at(i) << ": ";
    std::cout << "recuperato componente di tipo " << item.get_name();
    std::cout << " al tempo " << item.get_str_time();
    std::cout << std::fixed;
    std::cout << " in posizione " << std::setprecision(2) << item.get_pos();
    std::unique_lock<std::mutex> mtx_lck(mutex_box_count_);
    std::cout << " e inserito nella scatola " << n_box_count_ << std::endl;
}

void Monitor::print_mob_robot_message(size_t n_box) {
    std::unique_lock<std::mutex> cout_lck(cout_mutex_);
    std::cout << "Robot mobile: Recuperato la scatola " << n_box;
    std::cout << " e portata in magazzino\n";
}

bool Monitor::none_placing() {
    return std::all_of(placing_.cbegin(), placing_.cend(),
                        [](bool cobot_placing) { return cobot_placing == false; });
}

bool Monitor::find_box(size_t id, Box &box) {
    std::_List_const_iterator<Box> ptr = std::find_if(storage_.cbegin(), storage_.cend(),
            [&] (Box tmp) {return (tmp.get_id() == id); });
    if (ptr == storage_.cend())
        return false;

    else {
        box = *ptr;
        return true;
    }
}

std::string Monitor::find_box(size_t id) {
    Box box{0};

    if(find_box(id, box)) {
        std::string response{"La scatola n. " + std::to_string(id) + " contiene i prodotti { "};
        response.append(box.get_str_items() + "}\n");
        response.append(box.get_str_time_items());
        return response;
    }
    else {
        std::string err_msg {"la scatola n. " + std::to_string(id) + " non esiste\n"};
        return err_msg;
    }
}