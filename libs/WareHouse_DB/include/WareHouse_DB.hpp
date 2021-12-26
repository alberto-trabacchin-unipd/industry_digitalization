#ifndef WAREHOUSE_DB_HPP
#define WAREHOUSE_DB_HPP

#include <mutex>
#include <condition_variable>
#include <list>
#include <vector>
#include <string>
#include "Box.hpp"

extern std::mutex cout_mtx;


class WareHouse_DB {

public:
    WareHouse_DB() : n_boxes_(0) {}
    void stock_box(Box box);
    //Box* find_box(unsigned int id);
    void print_all_boxes();
    bool find_box(unsigned int id, Box &box);

private:
    std::list<Box> storage_;
    unsigned int n_boxes_;

    std::string get_str_info_box(Box box);

};

#endif