#ifndef RW_HPP
#define RW_HPP

#include <queue>
#include <mutex>
#include <condition_variable>

#include "Item.hpp"


class RW {

public:
    RW() : occupied_(false) {}

    void start_read();
    Item pop_data();
    void end_read();
    void start_write();
    void push_data(Item item);
    void end_write();


private:
    std::queue<Item> queue_items_;
    std::mutex mutex_;
    std::condition_variable canRead_;
    std::condition_variable canWrite_;
    bool occupied_;

};

#endif