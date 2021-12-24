#ifndef MVSYSTEM_HPP
#define MVSYSTEM_HPP

#include <string>
#include <queue>
#include "RW.hpp"

RW rw;

class MVSystem{

public:
    MVSystem();

    void read_data();
    void print_data();


private:
    
    std::string data_path_;

};

#endif