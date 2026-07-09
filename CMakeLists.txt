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
            src/model/input/InputHandler.cpp
            src/model/input/InputHandler.h
            src/SDL/EventSink.h
            src/SDL/EventPump.h
            src/gfx/GfxEventSink.h
            src/input/KeyboardSink.h
            src/gfx/GLRenderer.cpp
            src/gfx/GLRenderer.h
            ${GLAD_DIR}/src/glad.c
            src/gfx/Shader.h
            src/gfx/Shader.cpp
            src/gfx/Shader.h
            src/model/fcs/actions/Trim.h
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
