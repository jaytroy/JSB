cmake_minimum_required(VERSION 3.28)
project(CLIENT)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(IMGUI_DIR ../../external/imgui)
set(GLAD_DIR ../../external/glad)

find_package(PkgCOnfig REQUIRED)
find_package(SDL2 CONFIG REQUIRED)

add_executable(CLIENT
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
)

target_include_directories(JSB PRIVATE ${IMGUI_DIR} ${IMGUI_DIR}/backends ${GLAD_DIR}/include)

find_package(OpenGL REQUIRED)
find_package(glm CONFIG REQUIRED)

target_link_libraries(JSB PRIVATE
        OpenGL::GL
        ${CMAKE_DL_LIBS}
        glm::glm
        m
)

target_link_libraries(JSB PRIVATE SDL2::SDL2 SDL2::SDL2main)

target_compile_definitions(JSB PRIVATE SHADER_DIR="../client/src/gfx/shaders")
