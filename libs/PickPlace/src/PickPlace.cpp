#include <mutex>
#include <iostream>
#include "PickPlace.hpp"
#include "Box.hpp"
#include "Item.hpp"


PickPlace::PickPlace() :  cobot_box_(Box{1}), waiting_(2, true), n_box_(1), left_(false) {}


void PickPlace::start_put(unsigned int id) {
    std::unique_lock<std::mutex> mtx_lck(mutex_);

    while (!waiting_.at(OTHER_COBOT_ID) || cobot_box_.is_full() || (shutdown && !left_))
        canPush_.wait(mtx_lck);//
    //occupied_ = true;
    waiting_.at(id) = false;
}

void PickPlace::put_item(Item item) {
    cobot_box_.put_item(item);
}

void PickPlace::end_put(unsigned int id) {
    std::unique_lock<std::mutex> mtx_lck(mutex_);
    //occupied_ = false;

    if (shutdown) {
        if (waiting_.at(OTHER_COBOT_ID) && !cobot_box_.is_full()) {
            std::cout << "\nSveglio l'altro cobot...\n";
            if (waiting_.at(OTHER_COBOT_ID))
                std::cout << "true\n";
            canPush_.notify_one();
        }
        else {
            std::cout << "\nSveglio il mobile robot...\n";
            canCarry_.notify_one();
        }
        left_ = true;
        return;
    }

    waiting_.at(id) = true;
    if (cobot_box_.is_full())
        canCarry_.notify_one();
    else
        canPush_.notify_one();
}

void PickPlace::start_carry() {
    std::unique_lock<std::mutex> mtx_lck(mutex_);
    while (!waiting_.at(0) || !waiting_.at(1) || (!cobot_box_.is_full() && !shutdown))
        canCarry_.wait(mtx_lck);
}

Box PickPlace::carry_box() {
    return cobot_box_;
}

void PickPlace::end_carry() {
    std::unique_lock<std::mutex> mtx_lck(mutex_);
    cobot_box_ = Box{++n_box_};
    canPush_.notify_all();
}