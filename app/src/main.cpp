#include <string>
#include <iostream>
#include <thread>
#include <vector>

#include "data_mng.h"
#include "Monitor.hpp"


const unsigned int SPEED_FAC = 50;
unsigned int n_cobots = 2;
Monitor mon;
bool shutdown = false;


int main(int argc, char *argv[]) {
    std::vector<std::thread> mvs_threads;
    std::vector<std::thread> cobots_threads;

    std::vector<std::string> data_paths {
        "../mv_readings/arrivi_linea_a.txt",
        "../mv_readings/arrivi_linea_b.txt",
        "../mv_readings/arrivi_linea_c.txt"
    };

    check_input_param(argc);

    start_mvs_threads(mvs_threads, data_paths);
    start_cobot_threads(cobots_threads, argv);
    std::thread mobile_robot_thread(mobile_robot_thread_fun);
    std::thread graceful_exit_thread(graceful_exit_thread_fun);
    std::thread server_thread(server_thread_fun);


    for (auto &t : mvs_threads)
    t.join();

    for (auto &t : cobots_threads)
        t.join();

    mobile_robot_thread.join();
    graceful_exit_thread.join();
    server_thread.join();

    return 0;
}