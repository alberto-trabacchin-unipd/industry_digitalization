#include <iostream>
#include <string>

#include "MVSystem.hpp"
#include "Item.hpp"

int main(int argc, char *argv[]) {
    MVSystem mvs1{"../mv_readings/arrivi_linea_a.txt"};
    MVSystem mvs2{"../mv_readings/arrivi_linea_b.txt"};
    mvs1.read_data();
    mvs2.read_data();
    mvs1.get_last_item().print();
    mvs2.get_last_item().print();

    return 0;
}