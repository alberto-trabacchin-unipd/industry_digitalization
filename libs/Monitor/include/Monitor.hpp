#ifndef MONITOR_HPP
#define MONITOR_HPP

#include <vector>
#include <mutex>
#include <condition_variable>
#include <list>
#include <queue>
#include <string>

#include "Item.hpp"
#include "Box.hpp"

extern unsigned int n_cobots;


class Monitor {

public:
    Monitor();

    void write_data(size_t i, Item &item);
    Item read_data(size_t i);
    void place_item(Item &item);
    Box carry_box();

    void stock_box(Box &box) { storage_.push_back(box); };
    void print_cobot_message(size_t i, Item &item);
    void print_mob_robot_message(size_t n_box);
    bool none_placing();
    bool find_box(size_t id, Box &box);
    std::string find_box(size_t id);


    //Helper functions
    


private:
    std::vector<Item> item_data_;
    std::mutex mutex_data_;
    std::vector<std::condition_variable> canUseData_;
    std::vector<bool> data_ready_;

    Box cobots_box_;
    std::mutex mutex_box_;
    std::condition_variable canPlace;
    std::vector<bool> placing_;
    std::condition_variable canCarry;
    size_t n_box_count_;
    std::mutex mutex_box_count_;

    std::list<Box> storage_;

    std::mutex cout_mutex_;
};

#endif