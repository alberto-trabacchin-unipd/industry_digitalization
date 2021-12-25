#include <mutex>

#include "RW.hpp"
#include "Item.hpp"


void RW::start_read() {
    std::unique_lock<std::mutex> mtx_lck(mutex_);
    while (queue_items_.empty() || occupied_)
        canRead_.wait(mtx_lck);

    occupied_ = true;
}

Item RW::pop_data() {
    Item tmp = queue_items_.front();
    queue_items_.pop();
    return tmp;
}

void RW::end_read() {
    std::unique_lock<std::mutex> mtx_lck(mutex_);
    occupied_ = false;
    canWrite_.notify_one();
}

void RW::start_write() {
    std::unique_lock<std::mutex> mtx_lck(mutex_);
    while (occupied_)
        canWrite_.wait(mtx_lck);
    
    occupied_ = true;
}

void RW::push_data(Item item) {
    queue_items_.push(item);
}

void RW::end_write() {
    std::unique_lock<std::mutex> mtx_lck(mutex_);
    occupied_ = false;
    canRead_.notify_one();
}