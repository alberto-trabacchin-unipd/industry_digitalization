#include <string>
#include <fstream>
#include <iostream>
#include <algorithm>

#include "MVSystem.hpp"


MVSystem::MVSystem(const float distance, const float conv_speed, std::string data_src_path)
        : distance_(distance), conv_speed_(conv_speed), data_src_path_(data_src_path) {}

void MVSystem::read_data() {
    std::string str;

    std::ifstream fs(data_src_path_);
    while (std::getline(fs, str))
        data_.push_back(str);

    fs.close();
}

void MVSystem::print_data() {
    std::for_each(data_.cbegin(), data_.cend(),
                [](std::string line) { std::cout << line << std::endl; });
}