#include <mutex>
#include "PickPlace.hpp"
#include "Box.hpp"
#include "Item.hpp"


PickPlace::PickPlace() {
    occupied_ = false;
    box_avail_ = true;
    n_boxes = 0;
    box_ptr_ = place_new_box();
}

void PickPlace::start_put(unsigned int id) {
    std::unique_lock<std::mutex> mtx_lck(mutex_);

    while (occupied_ || box_ptr_->is_full()) {
        if (id == 1) {
            waiting1_ = true;
            canPush1_.wait(mtx_lck);
        }
        else if (id == 2) {
            waiting2_ = true;
            canPush2_.wait(mtx_lck);
        }
    }

    occupied_ = true;
}

void PickPlace::put_item(Item item) {
    box_ptr_->put_item(item);
}

void PickPlace::end_put(unsigned int id) {
    std::unique_lock<std::mutex> mtx_lck(mutex_);
    occupied_ = false;
    if (box_ptr_->is_full())
        canCarry_.notify_one();
    else if (id == 1) {
        waiting1_ = false;
        if (waiting2_) canPush2_.notify_one();
    }
    else if (id == 2) {
        waiting2_ = false;
        if (waiting1_) canPush1_.notify_one();
    }
}

void PickPlace::start_carry() {
    std::unique_lock<std::mutex> mtx_lck(mutex_);
    while (occupied_ || !box_ptr_->is_full())
        canCarry_.wait(mtx_lck);
    
    box_avail_ = false;
    occupied_ = true;
}

std::shared_ptr<Box> PickPlace::carry_box() {
    std::shared_ptr<Box> tmp = box_ptr_;
    box_ptr_ = place_new_box();
    return tmp;
}

void PickPlace::end_carry() {
    std::unique_lock<std::mutex> mtx_lck(mutex_);
    occupied_ = false;
    if (waiting1_)
        canPush1_.notify_one();
    else
        canPush2_.notify_one();
}