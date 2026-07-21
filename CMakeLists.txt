cmake_minimum_required(VERSION 3.28)
project(JSB)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(PkgConfig REQUIRED)
find_package(SDL2 CONFIG REQUIRED)
pkg_check_modules(JSBSIM REQUIRED JSBSim)

add_library(JSB_CORE STATIC
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
        src/input/Joystick.cpp
        src/input/Joystick.h
        src/simulation/input/InputHandler.cpp
        src/simulation/input/InputHandler.h
        src/SDL/EventSink.h
        src/SDL/EventPump.h
        src/input/KeyboardSink.hpp
        src/simulation/fcs/actions/Trim.hpp
        src/SimRunner.hpp
        src/input/InputDeviceFactory.hpp
        src/input/ControlBinding.h
        src/input/InputDeviceManager.hpp
        src/shared/FcsTarget.h
        src/simulation/fcs/actions/Trim.hpp
)

target_link_directories(JSB_CORE PUBLIC ${JSBSIM_LIBRARY_DIRS})

target_link_libraries(JSB_CORE PUBLIC
        /usr/lib/libJSBSim.a # fix this
        ${CMAKE_DL_LIBS}
        m
        SDL2::SDL2
)

target_include_directories(JSB_CORE PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        ${JSBSIM_INCLUDE_DIRS}
)

target_compile_definitions(JSB_CORE PUBLIC SRC_DIR="${CMAKE_CURRENT_SOURCE_DIR}/src/")



# Add graphics files if graphics is bundled. Otherwise build sim headless
if (IS_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/src/gfx")
    set(IMGUI_DIR ${CMAKE_CURRENT_SOURCE_DIR}/external/imgui)
    set(GLAD_DIR ${CMAKE_CURRENT_SOURCE_DIR}/external/glad)
    find_package(glm CONFIG REQUIRED)
    find_package(OpenGL REQUIRED)

    target_sources(JSB_CORE PRIVATE
            src/gfx/Window.cpp
            src/gfx/Window.h
            src/gfx/GLRenderer.cpp
            src/gfx/GLRenderer.h
            src/gfx/Shader.cpp
            src/gfx/Shader.h
            src/gfx/GfxEventSink.h
            src/gfx/Texture.h
            src/gfx/Texture.cpp
            ${IMGUI_DIR}/imgui.cpp
            ${IMGUI_DIR}/imgui_draw.cpp
            ${IMGUI_DIR}/imgui_tables.cpp
            ${IMGUI_DIR}/imgui_widgets.cpp
            ${IMGUI_DIR}/imgui_demo.cpp
            ${IMGUI_DIR}/backends/imgui_impl_sdl2.cpp
            ${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp
            ${GLAD_DIR}/src/glad.c
    )

    set(JSB_THIRD_PARTY
            ${IMGUI_DIR}/imgui.cpp
            ${IMGUI_DIR}/imgui_draw.cpp
            ${IMGUI_DIR}/imgui_tables.cpp
            ${IMGUI_DIR}/imgui_widgets.cpp
            ${IMGUI_DIR}/imgui_demo.cpp
            ${IMGUI_DIR}/backends/imgui_impl_sdl2.cpp
            ${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp
            ${GLAD_DIR}/src/glad.c
    )

    set_source_files_properties(
            ${JSB_THIRD_PARTY}
            PROPERTIES COMPILE_OPTIONS "-w"
    )

    target_include_directories(JSB_CORE PUBLIC
            ${IMGUI_DIR}
            ${IMGUI_DIR}/backends
            ${GLAD_DIR}/include
    )

    target_link_libraries(JSB_CORE PUBLIC
            OpenGL::GL
            glm::glm
    )

    target_compile_definitions(JSB_CORE PUBLIC SHADER_DIR="${CMAKE_CURRENT_SOURCE_DIR}/src/gfx/shaders/")
    target_compile_definitions(JSB_CORE PUBLIC TEXTURE_DIR="${CMAKE_CURRENT_SOURCE_DIR}/src/gfx/textures/")
endif ()


add_executable(JSB src/Main.cpp)
target_link_libraries(JSB PRIVATE JSB_CORE SDL2::SDL2main)


# Deployment builds (like docker) likely won't have the test dir
if (IS_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/test")
    list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/extras)
    include(CTest)
    add_subdirectory(test)
endif ()

target_compile_options(JSB PRIVATE -Wall -Wpedantic)
