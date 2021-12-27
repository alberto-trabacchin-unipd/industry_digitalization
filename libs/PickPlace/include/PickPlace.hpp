#ifndef PICK_PLACE_HPP
#define PICK_PLACE_HPP

#define OTHER_COBOT_ID ((id + 1) % 2)

#include "Box.hpp"
#include "Item.hpp"
#include <memory>
#include <vector>
#include <mutex>
#include <condition_variable>

extern bool shutdown;

class PickPlace {

public:
    PickPlace();
    void start_put(unsigned int id);
    void put_item(Item item);
    void end_put(unsigned int id);
    void start_carry();
    Box carry_box();
    void end_carry();
    unsigned int get_n_box() { return n_box_; };
    bool check_cobots_status() { return (waiting_.at(1) && waiting_.at(2)); };
    //std::shared_ptr<Box> place_new_box() { return std::make_shared<Box>(0); };

private:
    //std::shared_ptr<Box> box_ptr_;
    Box cobot_box_;//
    std::mutex mutex_;
    //std::condition_variable canPush1_;
    //std::condition_variable canPush2_;
    std::condition_variable canPush_;
    std::condition_variable canCarry_;
    //bool waiting1_;
    std::vector<bool> waiting_;//
   // bool waiting2_;
    //bool occupied_;
    //bool box_avail_;
    unsigned int n_box_;
    bool left_;
};

#endif