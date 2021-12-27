#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <iterator>

#include "Item.hpp"
#include "data_mng.h"


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
    int elaps_time =  static_cast<unsigned int>
                            (duration_cast<std::chrono::seconds>(t_end - t_begin).count());
    unsigned int t_conv = static_cast<unsigned int> (conv_len / conv_vel);

    unsigned int waiting_time = t_conv + MM*60 + SS - elaps_time;

    return waiting_time;

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