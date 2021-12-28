#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <thread>
#include <chrono>
#include <mutex>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <iostream>

#include "Item.hpp"
#include "data_mng.h"
#include "Box.hpp"
#include "Monitor.hpp"

auto t_start = std::chrono::steady_clock::now();


Item read_data(std::string line) {
    using namespace std;
    istringstream iss(line);
    vector<string> words { istream_iterator<string>{iss},
                            istream_iterator<string>{} };
    unsigned int MM = static_cast<unsigned int> (std::stoul(words.at(0)));
    unsigned int SS = static_cast<unsigned int> (std::stoul(words.at(1)));
    double position = stod(words.at(3));
    Item item{words.at(2), MM, SS, position};

    return item;
}

unsigned int calc_waiting_sec(std::chrono::steady_clock::time_point t_begin,
                                unsigned int MM, unsigned int SS, double conv_len, double conv_vel) {
                                    
    using std::chrono::steady_clock;
    using std::chrono::duration_cast;
    auto t_end = steady_clock::now();
    unsigned int elaps_time =  static_cast<unsigned int>
                            (duration_cast<std::chrono::milliseconds>(t_end - t_begin).count());
    unsigned int t_conv = static_cast<unsigned int> (1000 * conv_len / conv_vel);
    unsigned int t_mvs = (MM * 60 + SS) * 1000;

    //unsigned int waiting_time = (t_conv*1000 + MM*60*1000 + SS*1000 - elaps_time) / SPEED_FAC;
    unsigned int waiting_time = t_mvs - elaps_time + t_conv;

    return waiting_time / SPEED_FAC;

}

void set_pick_time(Item &item, double conv_len, double conv_vel) {
    unsigned int delta_sec = static_cast<unsigned int> (conv_len / conv_vel);
    unsigned int minutes = delta_sec / 60;
    unsigned int seconds = delta_sec % 60;

    if ((item.get_SS() + seconds) > 59) {
        item.set_MM(item.get_MM() + 1);
        seconds = seconds - (60 - item.get_SS());
        item.set_SS(seconds);
    }
    else
        item.set_SS(item.get_SS() + seconds);
    
    item.set_MM(item.get_MM() + minutes);   
}


void mv_system_thread_fun(size_t i, std::string data_path) {
    std::ifstream stream(data_path);
    if (!stream) {
        std::cerr << "Cannot open " << data_path;
        exit(EXIT_FAILURE);
    }
    std::string line;
    Item item{};

    while (!shutdown && getline(stream, line)) {
        mon.start_write(i);
        item = read_data(line);
        mon.send_item_cobot(i, item);
        mon.end_write(i);
    }
    std::cout << "Spegnendo MVS dopo pezzo " <<item.get_name() << std::endl;
}

void cobot_thread_fun(size_t i, double conv_len, double conv_vel) {
    using std::chrono::seconds;
    using std::chrono::milliseconds;
    using std::chrono::steady_clock;

    Item item{};
    size_t n_box;

    while (!shutdown) {
        mon.start_read(i);
        item = mon.read_item(i);
        mon.end_read(i);

        //sleep
        unsigned int waiting_millis = calc_waiting_sec(t_start, item.get_MM(), item.get_SS(), 
                                                        conv_len, conv_vel);
        
        std::cout << i << " deve aspettare per " << waiting_millis << " millisecondi\n";
        std::this_thread::sleep_for(milliseconds(waiting_millis));
        set_pick_time(item, conv_len, conv_vel);

        mon.start_place(i);
        mon.place_item(item);
        n_box = mon.get_n_box();
        mon.end_place(i);

        mon.print_cobot_message(i, item, n_box);
    }
    std::cout << "Spegnendo cobot...\n";
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

void server_thread_fun() {

}

void find_box(size_t id) {
    std::this_thread::sleep_for(std::chrono::seconds(40));
    Box box{0};
    mon.find_box(id, box);
    std::cout << box.get_str_items();
}

void check_input_param (int argc, std::vector<std::string> &data_paths) {
    if ((argc % 2) == 0 || static_cast<unsigned int> (argc/2) != n_cobots) {
        std::cerr << "ERR: input parameters are not valid\n";
        exit(EXIT_FAILURE);
    }
    size_t n = static_cast<size_t> (argc/2);
    if (n_cobots >= data_paths.size() || n >= data_paths.size()) {
        std::cerr << "ERR: too few file paths.\n";
        exit(EXIT_FAILURE);
    }
}

void start_mvs_threads(std::vector<std::thread> &mvs_threads, std::vector<std::string> &data_paths) {
    for (size_t i = 0, j = 1; i < n_cobots; i++, j = j+2)
        mvs_threads.push_back(std::thread(mv_system_thread_fun, i, data_paths.at(i)));
}

void start_cobot_threads(std::vector<std::thread> &cobot_threads, char *argv[]) {
    for (size_t i = 0, j = 1; i < n_cobots; i++, j = j+2)
        cobot_threads.push_back(std::thread(cobot_thread_fun, i,
                                            std::stod(argv[j]), std::stod(argv[j+1])));
}