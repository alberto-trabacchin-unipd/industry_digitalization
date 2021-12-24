#include <mutex>
#include <condition_variable>
#include <algorithm>
#include <iostream>

#include "WareHouse_DB.hpp"


DataBase::DataBase()
    : n_writers_(0),n_readers_(0), n_wait_writers_(0), n_wait_readers_(0) {}


void DataBase::start_write() {
    std::unique_lock<std::mutex> mtx_lck(mutex_);
    while (n_readers_ != 0 || n_writers_ != 0 || (n_wait_readers_ != 0 && !data_list_mv_.empty())) {
        n_wait_writers_++;
        canWrite_.wait(mtx_lck);
        n_wait_writers_--;
    }
    n_writers_++;
}


void DataBase::write_data(int data) {
    std::unique_lock<std::mutex> mtx_lck(mutex_);
    data_list_mv_.push_back(data);
}


void DataBase::end_write() {
    std::unique_lock<std::mutex> mtx_lck(mutex_);
    n_writers_--;
    if (n_writers_ == 0 && n_wait_readers_!= 0)
        canRead_.notify_all();
    else
        canWrite_.notify_one();
}


void DataBase::start_read() {
    std::unique_lock<std::mutex> mtx_lck(mutex_);
    while (n_writers_ != 0 || n_wait_writers_ != 0) {
        n_wait_readers_++;
        canWrite_.wait(mtx_lck);
        n_wait_writers_--;
    }
    n_readers_++;
}


int DataBase::read_data() {
    return 0;
}

void DataBase::end_read() {

}


void DataBase::print_data() {
    std::for_each(data_list_mv_.cbegin(), data_list_mv_.cend(),
            [](int i) { std::cout << i << std::endl; });
}