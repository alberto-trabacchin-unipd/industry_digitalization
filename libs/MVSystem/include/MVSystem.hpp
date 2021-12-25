#ifndef MVSYSTEM_HPP
#define MVSYSTEM_HPP

#include <string>
#include <queue>

#include "Item.hpp"
#include "RW.hpp"

extern RW rw;
extern std::mutex cout_mtx;


class MVSystem{

public:
    MVSystem(std::string data_path);
    void thread_fun();
    void read_data();
    Item get_last_item() { return queue_items_.back(); };

private:
    std::string data_path_;
    std::queue<Item> queue_items_;
};

#endif