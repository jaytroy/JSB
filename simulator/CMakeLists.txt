cmake_minimum_required(VERSION 3.28)
project(Simulator)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(PkgConfig REQUIRED)
pkg_check_modules(JSBSIM REQUIRED JSBSim)

add_executable(Simulator
        src/Main.cpp
        src/model/Aircraft.cpp
        src/model/Aircraft.h
        src/Simulation.cpp
        src/Simulation.h
        src/model/fcs/FcsStrategy.h
        src/model/fcs/actions/Throttle.h
        src/model/fcs/actions/Pitch.h
        src/model/fcs/actions/Roll.h
        src/model/fcs/actions/Yaw.h
        src/model/fcs/actions/Brake.h
        src/model/input/InputDevice.h
        src/model/fcs/FcsCommand.h
        src/model/fcs/FcsStrategyFactory.h
        src/model/fcs/actions/Engine.h
        src/model/fcs/actions/Trim.h
)

target_include_directories(Simulator PRIVATE ${JSBSIM_INCLUDE_DIRS})


target_link_directories(Simulator PRIVATE ${JSBSIM_LIBRARY_DIRS})
target_link_libraries(Simulator PRIVATE
        /usr/lib/libJSBSim.a
        ${CMAKE_DL_LIBS}
        m
)
