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
#include <queue>

#include "Item.hpp"
#include "data_mng.h"
#include "Box.hpp"
#include "Monitor.hpp"

bool shut_down = false;
std::mutex mtx_shutdown;
auto t_start = std::chrono::steady_clock::now();


void read_data(const std::string &data_path, std::queue<Item> &items_queue) {
    using namespace std;
    std::string line;

    std::ifstream stream(data_path);
    if (!stream) {
        std::cerr << "Cannot open " << data_path;
        exit(EXIT_FAILURE);
    }
    
    while (getline(stream, line)) {
        istringstream iss(line);
        vector<string> words{ istream_iterator<string>{iss},
                                istream_iterator<string>{} };
        const unsigned int MM = static_cast<unsigned int> (std::stoul(words.at(0)));
        const unsigned int SS = static_cast<unsigned int> (std::stoul(words.at(1)));
        const double position = stod(words.at(3));
        items_queue.push(Item{ words.at(2), MM, SS, position });
    }
}

unsigned int calc_waiting_millis(const unsigned int MM, const unsigned int SS,
                                 const double conv_len, const double conv_vel) {
                                    
    using std::chrono::steady_clock;
    using std::chrono::duration_cast;
    auto t_end = steady_clock::now();
    unsigned int elaps_time =  duration_cast<std::chrono::milliseconds>(t_end - t_start).count();
    unsigned int t_conv = static_cast<unsigned int> (1000 * conv_len / conv_vel);
    unsigned int t_mvs = (MM * 60 + SS) * 1000;
    unsigned int waiting_time = t_mvs / SPEED_FAC - elaps_time + t_conv / SPEED_FAC;

    return waiting_time;
}

void set_pick_time(Item &item, const double conv_len, const double conv_vel) {
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


void mv_system_thread_fun(const size_t i, const std::string &data_path,
                          const double conv_len, const double conv_vel) {
    std::queue<Item> items_queue;
    read_data(data_path, items_queue);
    
    while (!shut_down && !items_queue.empty()) {
        Item tmp = items_queue.front();
        items_queue.pop();
        unsigned int wait_time = calc_waiting_millis(tmp.get_MM(), tmp.get_SS(), 
                                                     conv_len, conv_vel);
        std::this_thread::sleep_for(std::chrono::milliseconds(wait_time));
        if (shut_down) break;
        mon.write_data(i, tmp);
    }
    print_exit_mvs_msg(i);
}

void cobot_thread_fun(const size_t i, const double conv_len, const double conv_vel) {
    while (!shut_down) {
        Item item = mon.read_data(i);
        if (shut_down) break;
        set_pick_time(item, conv_len, conv_vel);
        size_t box_id = mon.place_item(item);
        mon.print_cobot_message(i, item, box_id);
    }
    print_exit_cobot_msg(i);
}

void mobile_robot_thread_fun() {
    while (!shut_down) {
        Box mob_box = mon.carry_box();
        mon.stock_box(mob_box);
        mon.print_mob_robot_message(mob_box.get_id());
    }
    std::cout << "Spegnendo il robot mobile...\n";
}

void graceful_exit_thread_fun() {
    signal(SIGINT, [](int) { 
        mon.set_shutdown();
        std::cout << "\nSto ordinando lo spegnimento delle thread rimanenti...\n";
    });
}

void check_input_param (int argc, const std::vector<std::string> &data_paths) {
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

void start_mvs_threads(std::vector<std::thread> &mvs_threads,
                            const std::vector<std::string> &data_paths, char *argv[]) {

    for (size_t i = 0, j = 1; i < n_cobots; i++, j = j+2) {
        mvs_threads.push_back(std::thread(mv_system_thread_fun, i, std::ref(data_paths.at(i)),
                                            std::stod(argv[j]), std::stod(argv[j+1])));
    }
}

void start_cobot_threads(std::vector<std::thread> &cobot_threads, char *argv[]) {

    for (size_t i = 0, j = 1; i < n_cobots; i++, j = j+2) {
        cobot_threads.push_back(std::thread(cobot_thread_fun, i,
                                            std::stod(argv[j]), std::stod(argv[j+1])));
    }
}

void print_exit_cobot_msg(const size_t i) {
    const std::string str {"abcdefghijklmnopqrstuvwxyz"};
    std::unique_lock<std::mutex> cout_lck(mtx_cout);
    std::cout << "Spegnendo il cobot della linea di trasporto " << str.at(i) << "...\n";
}

void print_exit_mvs_msg(const size_t i) {
    const std::string str {"abcdefghijklmnopqrstuvwxyz"};
    std::unique_lock<std::mutex> cout_lck(mtx_cout);
    std::cout << "Spegnendo il sistema di visione della linea di trasporto " << str.at(i) << "...\n";
}