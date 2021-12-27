#ifndef DATA_MNG_H
#define DATA_MNG_H

#include <fstream>
#include <chrono>
#include "Item.hpp"

Item read_data(std::string line);
unsigned int calc_waiting_sec(std::chrono::steady_clock::time_point t_begin,
                                unsigned int MM, unsigned int SS, double conv_len, double conv_vel);

void set_pick_time(Item &item, double conv_len, double conv_vel);


#endif