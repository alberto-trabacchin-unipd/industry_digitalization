cmake_minimum_required( VERSION 3.10.2)

project( Main_application
         VERSION 1.0
         DESCRIPTION "Developing main application" )

add_executable(application src/main.cpp)

target_link_libraries(application
    #Link below libraries for building the application (exa. PRIVATE PSE::libraryname)
    PRIVATE PSE::WareHouse_DB
    PRIVATE PSE::MVSystem
    PRIVATE PSE::RW
    PRIVATE PSE::PickPlace
    PRIVATE PSE::MobileRobot
    PRIVATE PSE::Cobot
    PRIVATE PSE::Box
    PRIVATE PSE::Item
    PRIVATE pthread
)