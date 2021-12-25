#include <iostream>
#include <thread>
#include <mutex>

#include "MVSystem.hpp"
#include "Cobot.hpp"

std::mutex cout_mtx;


int main(int argc, char *argv[]) {
    MVSystem mvs1{"../mv_readings/arrivi_linea_a.txt"};
    MVSystem mvs2{"../mv_readings/arrivi_linea_b.txt"};
    Cobot cobot1{1, 10, &mvs1, "1"};
    Cobot cobot2{1, 10, &mvs2, "2"};

    std::thread mvs1_thread(&MVSystem::thread_fun, &mvs1);
    std::thread mvs2_thread(&MVSystem::thread_fun, &mvs2);
    std::thread cobot1_thread(&Cobot::thread_fun, &cobot1);
    std::thread cobot2_thread(&Cobot::thread_fun, &cobot2);

    mvs1_thread.join();
    mvs2_thread.join();
    cobot1_thread.join();
    cobot2_thread.join();

    return 0;
}