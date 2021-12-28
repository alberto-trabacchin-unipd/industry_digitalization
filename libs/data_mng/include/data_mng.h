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
void mv_system_thread_fun(size_t i, std::string data_path);
void cobot_thread_fun(size_t i, double conv_len, double conv_vel);
void mobile_robot_thread_fun();
void my_handler(int s);
void graceful_exit_thread_fun();
void server_thread_fun();
void find_box(size_t id);

unsigned int check_input_param (int argc);


#endif