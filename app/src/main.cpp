#include <iostream>
#include <thread>
#include <mutex>

#include "MVSystem.hpp"
#include "Cobot.hpp"
#include "MobileRobot.hpp"

std::mutex cout_mtx;


int main(int argc, char *argv[]) {
    if (argc != 5) {
        std::cerr << "Parameters not valid\n" << std::endl;
        exit(EXIT_FAILURE);
    }

    MVSystem mvs1{"../mv_readings/arrivi_linea_a.txt"};
    MVSystem mvs2{"../mv_readings/arrivi_linea_b.txt"};
    Cobot cobot1{argv[1], argv[2], &mvs1, "1"};
    Cobot cobot2{argv[3], argv[4], &mvs2, "2"};
    MobileRobot mobile_robot{};

    std::thread mvs1_thread(&MVSystem::thread_fun, &mvs1);
    std::thread mvs2_thread(&MVSystem::thread_fun, &mvs2);
    std::thread cobot1_thread(&Cobot::thread_fun, &cobot1, "1");
    std::thread cobot2_thread(&Cobot::thread_fun, &cobot2, "2");
    std::thread mobile_robot_thread(&MobileRobot::thread_fun, &mobile_robot);

    mvs1_thread.join();
    mvs2_thread.join();
    cobot1_thread.join();
    cobot2_thread.join();
    mobile_robot_thread.join();

    return 0;
}