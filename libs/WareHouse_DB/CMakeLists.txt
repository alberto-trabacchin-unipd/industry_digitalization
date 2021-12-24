cmake_minimum_required( VERSION 3.10.2 )

project(warehouse_database_lib
        VERSION 0.1
        DESCRIPTION "Defines Data type exchanged between Database, Machine Vision systems and cobot."
        )

add_library(WareHouse_DB STATIC src/WareHouse_DB.cpp)

target_include_directories(WareHouse_DB
        PUBLIC include
        )

target_link_libraries(WareHouse_DB
        )

add_library(PSE::WareHouse_DB ALIAS WareHouse_DB)