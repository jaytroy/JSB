cmake_minimum_required(VERSION 3.16)
project(JSB)

find_package(PkgConfig REQUIRED)
find_package(Curses REQUIRED)
pkg_check_modules(JSBSIM REQUIRED IMPORTED_TARGET JSBSim)

add_executable(JSB main.cpp
)

target_include_directories(JSB PRIVATE
        /usr/include
        /usr/include/JSBSim
)

target_link_libraries(JSB PRIVATE JSBSim)
target_link_libraries(JSB PRIVATE ${CURSES_LIBRARIES})