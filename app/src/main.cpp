#include <string>
#include <fstream>
#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

#include "data_mng.h"
#include "Monitor.hpp"
#include "Item.hpp"
#include "Box.hpp"


const unsigned int SPEED_FAC = 50;
unsigned int n_cobots = 2;

Monitor mon;
bool shutdown = false;


int main(int argc, char *argv[]) { //Ricordati di fare il programma dove si impostano 2*n parametri
    if ((argc % 2) == 0 ) {
        std::cerr << "ERR: input parameters are not valid\n";
        exit(EXIT_FAILURE);
    }

    std::thread mvs1_thread(mv_system_thread_fun, 0, "../mv_readings/arrivi_linea_a.txt");
    std::thread mvs2_thread(mv_system_thread_fun, 1, "../mv_readings/arrivi_linea_b.txt");
    
    std::thread cobot1_thread(cobot_thread_fun, 0, std::stod(argv[1]), std::stod(argv[2]));
    std::thread cobot2_thread(cobot_thread_fun, 1, std::stod(argv[3]), std::stod(argv[4]));


    std::thread mobile_robot_thread(mobile_robot_thread_fun);
    std::thread graceful_exit_thread(graceful_exit_thread_fun);
    std::thread server_thread(server_thread_fun);

    find_box(2);

    mvs1_thread.join();
    mvs2_thread.join();
    cobot1_thread.join();
    cobot2_thread.join();
    mobile_robot_thread.join();
    graceful_exit_thread.join();
    server_thread.join();

    return 0;
}