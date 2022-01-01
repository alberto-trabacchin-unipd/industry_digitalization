#ifndef DATA_MNG_H
#define DATA_MNG_H

#define UNUSED(x) (void)(x)

#include <fstream>
#include <chrono>
#include <queue>
#include "Item.hpp"
#include "Monitor.hpp"


extern Monitor mon;
extern std::mutex mtx_cout;
extern const unsigned int SPEED_FAC;

void read_data(const std::string &data_path, std::queue<Item> &items_queue);
unsigned int calc_waiting_millis(const unsigned int MM, const unsigned int SS,
                                 const double conv_len, const double conv_vel);
void set_pick_time(Item &item, const double conv_len, const double conv_vel);

//Threads function
void mv_system_thread_fun(const size_t i, const std::string &data_path,
                          const double conv_len, const double conv_vel);
void cobot_thread_fun(const size_t i, const double conv_len, const double conv_vel);
void mobile_robot_thread_fun();
void graceful_exit_thread_fun();

//Helper functions...
void find_box(const size_t id);
void check_input_param (int argc, const std::vector<std::string> &data_paths);
void start_mvs_threads(std::vector<std::thread> &mvs_threads,
                            const std::vector<std::string> &data_paths, char *argv[]);

void start_cobot_threads(std::vector<std::thread> &cobot_threads, char *argv[]);
void join_threads();
int setup_conn();
void print_exit_cobot_msg(const size_t i);
void print_exit_mvs_msg(const size_t i);

#endif