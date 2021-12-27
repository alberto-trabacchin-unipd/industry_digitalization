#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

#include "MVSystem.hpp"
#include "Cobot.hpp"
#include "MobileRobot.hpp"
#include "WareHouse_DB.hpp"
#include "Box.hpp"
#include "Item.hpp"
#include "Monitor.hpp"

std::mutex cout_mtx;
WareHouse_DB whdb;
bool shutdown = false;


void my_handler(int s){
    shutdown = true;
    std::cout << "\nSto ordinando lo spegnimento delle thread...\n";
}

void graceful_exit_proc() {
    struct sigaction sigIntHandler;

    sigIntHandler.sa_handler = my_handler;
    sigemptyset(&sigIntHandler.sa_mask);
    sigIntHandler.sa_flags = 0;

    sigaction(SIGINT, &sigIntHandler, NULL);

    pause();
}


int main(int argc, char *argv[]) {
    if (argc != 5) {
        std::cerr << "ERR: input parameters are not valid\n";
        exit(EXIT_FAILURE);
    }

    MVSystem mvs1{"../mv_readings/arrivi_linea_a.txt"};
    MVSystem mvs2{"../mv_readings/arrivi_linea_b.txt"};
    Cobot cobot1{argv[1], argv[2], std::ref(mvs1), 1};
    Cobot cobot2{argv[3], argv[4], std::ref(mvs2), 2};
    MobileRobot mobile_robot{};

    std::thread mvs1_thread(&MVSystem::thread_fun, &mvs1);
    std::thread mvs2_thread(&MVSystem::thread_fun, &mvs2);
    std::thread cobot1_thread(&Cobot::thread_fun, &cobot1);
    std::thread cobot2_thread(&Cobot::thread_fun, &cobot2);
    std::thread mobile_robot_thread(&MobileRobot::thread_fun, &mobile_robot);
    std::thread mythread(graceful_exit_proc);

    
    std::this_thread::sleep_for(std::chrono::seconds(20));

    Box my_box{0};
    if (whdb.find_box(5, my_box))
        std::cout << my_box.get_str_items() << std::endl;

    mvs1_thread.join();
    mvs2_thread.join();
    cobot1_thread.join();
    cobot2_thread.join();
    mobile_robot_thread.join();
    mythread.join();


    return 0;
}