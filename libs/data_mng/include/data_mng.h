#ifndef DATA_MNG_H
#define DATA_MNG_H

#include <fstream>
#include <chrono>
#include "Item.hpp"
#include "Monitor.hpp"

extern Monitor mon;
extern const unsigned int SPEED_FAC;
extern bool shutdown;

Item read_data(std::string line);
unsigned int calc_waiting_sec(std::chrono::steady_clock::time_point t_begin,
                                unsigned int MM, unsigned int SS, double conv_len, double conv_vel);
void set_pick_time(Item &item, double conv_len, double conv_vel);

//Threads function
void mv_system_thread_fun(size_t i, std::string data_path);
void cobot_thread_fun(size_t i, double conv_len, double conv_vel);
void mobile_robot_thread_fun();
void my_handler(int s);
void graceful_exit_thread_fun();
void server_thread_fun();

//Helper functions...
void find_box(size_t id);
void check_input_param (int argc, std::vector<std::string> &data_paths);
void start_mvs_threads(std::vector<std::thread> &mvs_threads, std::vector<std::string> &data_paths);
void start_cobot_threads(std::vector<std::thread> &cobot_threads, char *argv[]);
void join_threads();

#endif