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


Monitor mon;
bool shutdown = false;


void mv_system_thread_fun(size_t i, std::string data_path) {
    std::ifstream stream(data_path);
    std::string line;
    Item item{};

    while (getline(stream, line)) {
        mon.start_write(i);
        item = read_data(line);
        mon.send_item_cobot(i, item);
        mon.end_write(i);
    }
}

void cobot_thread_fun(size_t i, double conv_len, double conv_vel) {
    using std::chrono::seconds;
    using std::chrono::steady_clock;

    Item item{};
    size_t n_box;
    auto t_start = steady_clock::now();

    while (true) {
        mon.start_read(i);
        item = mon.read_item(i);
        mon.end_read(i);

        //sleep
        unsigned int waiting_seconds = calc_waiting_sec(t_start, item.get_MM(), item.get_SS(), 
                                                        conv_len, conv_vel);
        
        std::this_thread::sleep_for(seconds(waiting_seconds));
        set_pick_time(item, conv_len, conv_vel);

        mon.start_place(i);
        mon.place_item(item);
        n_box = mon.get_n_box();
        mon.end_place(i);

        mon.print_cobot_message(i, item, n_box);
    }
}

void mobile_robot_thread_fun() {
    size_t mob_box_id;
    while (true) {
        mon.start_carry();
        mon.carry_box();
        mob_box_id = mon.get_mob_box_id();
        mon.end_carry();

        mon.stock_box();
        mon.print_mob_robot_message(mob_box_id);
    }
}


void my_handler(int s){
    shutdown = true;
    std::cout << "\nSto ordinando lo spegnimento delle thread...\n";
}

void graceful_exit_thread_fun() {
    struct sigaction sigIntHandler;

    sigIntHandler.sa_handler = my_handler;
    sigemptyset(&sigIntHandler.sa_mask);
    sigIntHandler.sa_flags = 0;

    sigaction(SIGINT, &sigIntHandler, NULL);

    pause();
}

void find_box(size_t id) {
    std::this_thread::sleep_for(std::chrono::seconds(40));
    Box box{0};
    mon.find_box(id, box);
    std::cout << box.get_str_items();
}

int main(int argc, char *argv[]) { //Ricordati di fare il programma dove si impostano 2*n parametri
    if (argc != 5) {
        std::cerr << "ERR: input parameters are not valid\n";
        exit(EXIT_FAILURE);
    }

    std::thread mvs1_thread(mv_system_thread_fun, 0, "../mv_readings/arrivi_linea_a.txt");
    std::thread mvs2_thread(mv_system_thread_fun, 1, "../mv_readings/arrivi_linea_b.txt");
    
    std::thread cobot1_thread(cobot_thread_fun, 0, std::stod(argv[1]), std::stod(argv[2]));
    std::thread cobot2_thread(cobot_thread_fun, 1, std::stod(argv[3]), std::stod(argv[4]));

    std::thread mobile_robot_thread(mobile_robot_thread_fun);

    std::thread graceful_exit_thread(graceful_exit_thread_fun);

    find_box(2);

    mvs1_thread.join();
    mvs2_thread.join();
    cobot1_thread.join();
    cobot2_thread.join();
    mobile_robot_thread.join();
    graceful_exit_thread.join();

    return 0;
}