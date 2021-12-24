#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <iostream>
#include <algorithm>
#include <iterator>

#include "MVSystem.hpp"
#include "Item.hpp"


MVSystem::MVSystem(std::string data_path)
        : data_path_(data_path) {}

void MVSystem::thread_fun() {

}

void MVSystem::read_data() {
    using namespace std;
    ifstream file(data_path_);

    if (!file) {
        cout << "ERR: cannot open file\n";
        exit(EXIT_FAILURE);
    }
    else if (file.peek() == ifstream::traits_type::eof()) {
        cerr << "ERR: file at '" << data_path_ << "' is empty\n";
        exit(EXIT_FAILURE);
    }

    string line;
    while (getline(file, line)) {
        istringstream iss(line);
        vector<string> words { istream_iterator<string>{iss},
                               istream_iterator<string>{} };
        unsigned int pick_min = static_cast<unsigned int> (std::stoul(words.at(0)));
        unsigned int pick_sec = static_cast<unsigned int> (std::stoul(words.at(1)));
        double position = stod(words.at(3));
        Item tmp_item {pick_min, pick_sec, words.at(2), position};
        queue_items_.push(tmp_item);
    }
}
