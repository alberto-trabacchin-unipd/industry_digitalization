#ifndef WAREHOUSE_DB_HPP
#define WAREHOUSE_DB_HPP

#include <vector>
#include <mutex>
#include <condition_variable>


class DataBase {

public:
    DataBase();

    void start_write();
    void write_data(int data);
    void end_write();

    void start_read();
    int read_data();
    void end_read();

    void print_data();


private:
    std::vector<int> data_list_mv_;
    std::mutex mutex_;
    std::condition_variable canWrite_;
    std::condition_variable canRead_;
    std::vector<int> data_list_wh_;

    size_t n_writers_;
    size_t n_readers_;
    size_t n_wait_writers_;
    size_t n_wait_readers_;

};

#endif