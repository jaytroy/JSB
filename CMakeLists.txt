cmake_minimum_required(VERSION 3.16)
project(JSB)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(PkgConfig REQUIRED)
find_package(Curses REQUIRED)
pkg_check_modules(JSBSIM REQUIRED JSBSim)

add_executable(JSB src/Main.cpp
        src/model/Aircraft.cpp
        src/model/Aircraft.h
        src/util/NCursesManager.cpp
        src/util/NCursesManager.h
        src/Simulation.cpp
        src/Simulation.h
        src/model/fcs/FcsStrategy.cpp
        src/model/fcs/FcsStrategy.h
        src/model/fcs/actions/Throttle.cpp
        src/model/fcs/actions/Throttle.h
        src/model/fcs/actions/Pitch.cpp
        src/model/fcs/actions/Pitch.h
        src/model/fcs/actions/Roll.cpp
        src/model/fcs/actions/Roll.h
        src/model/fcs/actions/Yaw.cpp
        src/model/fcs/actions/Yaw.h
        src/model/fcs/actions/Brake.cpp
        src/model/fcs/actions/Brake.h
        src/model/fcs/Input.cpp
        src/model/fcs/Input.h
        src/util/InputDevice.h
        src/model/fcs/FcsCommand.h
)

target_include_directories(JSB PRIVATE ${JSBSIM_INCLUDE_DIRS})
target_link_libraries(JSB PRIVATE ${JSBSIM_LIBRARIES})
target_link_directories(JSB PRIVATE ${JSBSIM_LIBRARY_DIRS})
target_link_libraries(JSB PRIVATE ${CURSES_LIBRARIES})