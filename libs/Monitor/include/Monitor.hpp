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

extern bool shut_down;
extern unsigned int n_cobots;


class Monitor {

public:
    Monitor();

    void start_write(size_t i);
    void send_item_cobot(size_t i, std::queue<Item> &items_queue);
    void end_write(size_t i);

    void start_read(size_t i);
    Item read_item(size_t i) { return item_data_.at(i); };
    void end_read(size_t i);

    void start_place(size_t i);
    void place_item(Item &item);
    void end_place(size_t i);

    void start_carry();
    void carry_box() { mobile_box_ = cobots_box_; };
    void end_carry();

    void stock_box() { storage_.push_back(mobile_box_); };
    size_t get_n_box() { return n_boxes_; };
    size_t get_mob_box_id() { return mobile_box_.get_id(); };
    void print_cobot_message(size_t i, Item &item, size_t n_box);
    void print_mob_robot_message(size_t n_box);
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

    Box mobile_box_;
    size_t n_boxes_;
    std::list<Box> storage_;

    std::mutex cout_mutex_;
};

#endif