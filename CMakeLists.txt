cmake_minimum_required(VERSION 3.16)
project(JSB)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(PkgConfig REQUIRED)
find_package(Curses REQUIRED)
pkg_check_modules(JSBSIM REQUIRED IMPORTED_TARGET JSBSim)

add_executable(JSB src/main.cpp
        src/model/aircraft.cpp
        src/model/aircraft.h
        src/util/nCursesManager.cpp
        src/util/nCursesManager.h
        src/simulation.cpp
        src/simulation.h
        src/model/fcs/fcsStrategy.cpp
        src/model/fcs/fcsStrategy.h
        src/model/fcs/throttle.cpp
        src/model/fcs/throttle.h
)

target_link_libraries(JSB PRIVATE PkgConfig::JSBSim)
target_link_libraries(JSB PRIVATE ${CURSES_LIBRARIES})