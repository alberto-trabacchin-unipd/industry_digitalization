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
extern bool shut_down;
extern std::mutex mtx_shutdown;

class Monitor {

public:
    Monitor();

    void write_data(const size_t i, const Item &item);
    Item read_data(const size_t i);
    size_t place_item(const Item &item);
    Box carry_box();

    void stock_box(const Box &box) { storage_.push_back(box); };
    void print_cobot_message(const size_t i, Item &item, const size_t box_id);
    void print_mob_robot_message(const size_t n_box);
    bool none_placing();
    bool find_box(const size_t id, Box &box);
    std::string find_box(const size_t id);
    void set_shutdown();


    //Helper functions
    


private:
    std::vector<Item> item_data_;
    std::vector<std::mutex> mutex_data_;
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

    std::vector<bool> end_data;
};

#endif