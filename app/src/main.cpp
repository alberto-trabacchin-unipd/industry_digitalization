#include <iostream>
#include <thread>
#include <mutex>

#include "MVSystem.hpp"

std::mutex cout_mtx;


int main(int argc, char *argv[]) {
    MVSystem mvs1{"../mv_readings/arrivi_linea_a.txt"};
    MVSystem mvs2{"../mv_readings/arrivi_linea_b.txt"};
    
    std::thread mvs1_thread(&MVSystem::thread_fun, &mvs1);
    std::thread mvs2_thread(&MVSystem::thread_fun, &mvs2);

    mvs1_thread.join();
    mvs2_thread.join();

    return 0;
}