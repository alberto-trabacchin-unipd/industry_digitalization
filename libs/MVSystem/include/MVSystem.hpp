#ifndef MVSYSTEM_HPP
#define MVSYSTEM_HPP

#include <string>
#include <vector>

class MVSystem{

public:
    MVSystem(const float distance, const float conv_speed, const std::string data_src_path);

    void read_data();
    void print_data();


private:
    const float distance_;
    const float conv_speed_;
    std::string data_src_path_;
    std::vector<std::string> data_;

};

#endif