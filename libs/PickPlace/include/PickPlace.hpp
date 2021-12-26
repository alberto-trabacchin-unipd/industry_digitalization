#ifndef PICK_PLACE_HPP
#define PICK_PLACE_HPP

#include "Box.hpp"
#include "Item.hpp"
#include <memory>
#include <mutex>
#include <condition_variable>

class PickPlace {

public:
    PickPlace();
    void start_put(unsigned int id);
    void put_item(Item item);
    void end_put(unsigned int id);
    void start_carry();
    std::shared_ptr<Box> carry_box();
    void end_carry();
    std::shared_ptr<Box> place_new_box() { return std::make_shared<Box>(0); };

private:
    std::shared_ptr<Box> box_ptr_;
    std::mutex mutex_;
    std::condition_variable canPush1_;
    std::condition_variable canPush2_;
    std::condition_variable canCarry_;
    bool waiting1_;
    bool waiting2_;
    bool occupied_;
    bool box_avail_;
};

#endif