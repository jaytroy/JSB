cmake_minimum_required(VERSION 3.16)
project(JSB)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(PkgConfig REQUIRED)
find_package(Curses REQUIRED)
pkg_check_modules(JSBSIM REQUIRED JSBSim)

add_executable(JSB src/main.cpp
        src/model/aircraft.cpp
        src/model/aircraft.h
        src/util/nCursesManager.cpp
        src/util/nCursesManager.h
        src/simulation.cpp
        src/simulation.h
        src/model/fcs/fcsStrategy.cpp
        src/model/fcs/fcsStrategy.h
        src/model/fcs/actions/throttle.cpp
        src/model/fcs/actions/throttle.h
        src/model/fcs/actions/pitch.cpp
        src/model/fcs/actions/pitch.h
        src/model/fcs/actions/roll.cpp
        src/model/fcs/actions/roll.h
        src/model/fcs/actions/yaw.cpp
        src/model/fcs/actions/yaw.h
        src/model/fcs/actions/brake.cpp
        src/model/fcs/actions/brake.h
        src/model/fcs/input.cpp
        src/model/fcs/input.h
)

target_include_directories(JSB PRIVATE ${JSBSIM_INCLUDE_DIRS})
target_link_libraries(JSB PRIVATE ${JSBSIM_LIBRARIES})
target_link_directories(JSB PRIVATE ${JSBSIM_LIBRARY_DIRS})
target_link_libraries(JSB PRIVATE ${CURSES_LIBRARIES})