//
// Created by jay on 7/2/26.
//

#include "Window.h"

#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_opengl3.h"

#include <SDL.h>
#include <stdexcept>

#include "glad/glad.h"

Window::Window() { //Give it an abstract implementation
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        throw std::runtime_error("SDL video init failed");
    }

    //Set OpenGL atributes
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    //SDL window setup
    window_ = SDL_CreateWindow("Flight Sim", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
    if (!window_) {
        SDL_Quit();
        throw std::runtime_error("SDL window init failed");
    }

    //Setup OpenGL
    gl_ = SDL_GL_CreateContext(window_);
    if (!gl_) {
        SDL_DestroyWindow(window_);
        SDL_Quit();
        throw std::runtime_error("OpenGL renderer init failed");
    }
    if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
        SDL_DestroyWindow(window_);
        SDL_Quit();
        throw std::runtime_error("GLAD failed to initialize");
    }
    SDL_GL_SetSwapInterval(1); //GL window swapping

    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

    renderer_ = std::make_unique<GLRenderer>();

    //ImGui setup
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.FontGlobalScale = 1.5f;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

    ImGui::StyleColorsDark();
    ImGui::GetStyle().ScaleAllSizes(1.5f);

    ImGui_ImplSDL2_InitForOpenGL(window_, gl_);
    ImGui_ImplOpenGL3_Init("#version 330");
}

void Window::cleanup() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();

    SDL_DestroyWindow(window_);
    SDL_Quit();
}

void Window::renderFrame(std::vector<double>& payload) {
    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    glClearColor(0.1f, 0.1f, 0.15f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    renderGraphics(payload);
    renderGUI(payload);
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    SDL_GL_SwapWindow(window_);
}

void Window::renderGUI(std::vector<double> &payload) {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();

    //All relevant info
    ImGui::SetNextWindowSize(ImVec2(500, 500), ImGuiCond_FirstUseEver);
    ImGui::Begin("Flight controls");
    ImGui::Text("Sim time: %lf", payload[0]);
    ImGui::Text("North-South position: %lf", payload[1]);
    ImGui::Text("East-West position: %lf", payload[2]);
    ImGui::Text("Up-Down position: %lf", payload[3]);
    ImGui::Text("Heading: %lf", payload[4]);
    ImGui::Text("Airspeed: %lf", payload[5]);
    ImGui::Text("Throttle: %lf", payload[6]);
    ImGui::Text("Rpm: %lf", payload[7]);
    ImGui::Text("Pitch: %lf", payload[8]);
    ImGui::Text("Roll: %lf", payload[9]);
    ImGui::Text("Brake: %lf", payload[10]);

    ImGui::End();
    ImGui::Render();
}

void Window::renderGraphics(std::vector<double>& payload) {
    renderer_->render(payload);
}
