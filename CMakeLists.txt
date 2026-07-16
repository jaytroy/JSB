    cmake_minimum_required(VERSION 3.28)
    project(JSB)

    set(CMAKE_CXX_STANDARD 20)
    set(CMAKE_CXX_STANDARD_REQUIRED ON)
    set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
    set(IMGUI_DIR ${CMAKE_CURRENT_SOURCE_DIR}/external/imgui)
    set(GLAD_DIR ${CMAKE_CURRENT_SOURCE_DIR}/external/glad)

    find_package(PkgConfig REQUIRED)
    find_package(SDL2 CONFIG REQUIRED)
    pkg_check_modules(JSBSIM REQUIRED JSBSim)

    add_executable(JSB
            src/Main.cpp
            src/simulation/Aircraft.cpp
            src/simulation/Aircraft.h
            src/simulation/Simulation.cpp
            src/simulation/Simulation.h
            src/simulation/fcs/FcsStrategy.h
            src/simulation/fcs/actions/Throttle.hpp
            src/simulation/fcs/actions/Pitch.hpp
            src/simulation/fcs/actions/Roll.hpp
            src/simulation/fcs/actions/Yaw.hpp
            src/simulation/fcs/actions/Brake.hpp
            src/shared/AxisDevice.hpp
            src/shared/FcsCommand.h
            src/simulation/fcs/FcsStrategyFactory.hpp
            src/simulation/fcs/actions/Engine.hpp
            src/gfx/Window.cpp
            src/gfx/Window.h
            ${IMGUI_DIR}/imgui.cpp
            ${IMGUI_DIR}/imgui_draw.cpp
            ${IMGUI_DIR}/imgui_tables.cpp
            ${IMGUI_DIR}/imgui_widgets.cpp
            ${IMGUI_DIR}/imgui_demo.cpp
            ${IMGUI_DIR}/backends/imgui_impl_sdl2.cpp
            ${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp
            src/input/Joystick.cpp
            src/input/Joystick.h
            src/simulation/input/InputHandler.cpp
            src/simulation/input/InputHandler.h
            src/SDL/EventSink.h
            src/SDL/EventPump.h
            src/gfx/GfxEventSink.h
            src/input/KeyboardSink.hpp
            src/gfx/GLRenderer.cpp
            src/gfx/GLRenderer.h
            ${GLAD_DIR}/src/glad.c
            src/gfx/Shader.h
            src/gfx/Shader.cpp
            src/gfx/Shader.h
            src/simulation/fcs/actions/Trim.hpp
            src/SimRunner.hpp
            src/input/InputDeviceFactory.hpp
            src/input/ControlBinding.h
            src/input/InputDeviceManager.hpp
            src/shared/FcsTarget.h
    )

    target_include_directories(JSB PRIVATE ${JSBSIM_INCLUDE_DIRS})
    target_include_directories(JSB PRIVATE ${IMGUI_DIR} ${IMGUI_DIR}/backends ${GLAD_DIR}/include)

    find_package(OpenGL REQUIRED)
    find_package(glm CONFIG REQUIRED)

    target_link_directories(JSB PRIVATE ${JSBSIM_LIBRARY_DIRS})
    target_link_libraries(JSB PRIVATE
            /usr/lib/libJSBSim.a
            OpenGL::GL
            ${CMAKE_DL_LIBS}
            glm::glm
            m
    )
    target_link_libraries(JSB PRIVATE SDL2::SDL2 SDL2::SDL2main)

    target_compile_definitions(JSB PRIVATE SHADER_DIR="${CMAKE_CURRENT_SOURCE_DIR}/src/gfx/shaders/")
    target_compile_definitions(JSB PRIVATE TEXTURE_DIR="${CMAKE_CURRENT_SOURCE_DIR}/src/gfx/textures/")
    target_compile_definitions(JSB PRIVATE SRC_DIR="${CMAKE_CURRENT_SOURCE_DIR}/src/")

    #target_compile_options(JSB PRIVATE -Wall -Wpedantic)