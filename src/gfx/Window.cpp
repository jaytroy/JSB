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
#include "networking/UdpServer.hpp"

Window::Window() { //Give it an abstract implementation
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        throw std::runtime_error("SDL video init failed");
    }

    //Set OpenGL attributes
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

Window::~Window() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();

    SDL_DestroyWindow(window_);
    SDL_Quit();
}

void Window::renderFrame(RendererPayload& payload) {
    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    glClearColor(0.1f, 0.1f, 0.15f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    server_.receive();

    renderGraphics(payload);
    renderGUI(payload);
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    SDL_GL_SwapWindow(window_);
}

void Window::renderGUI(const RendererPayload &payload) {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();

    //All relevant info
    ImGui::SetNextWindowSize(ImVec2(500, 500), ImGuiCond_FirstUseEver);
    ImGui::Begin("Flight controls");
    ImGui::Text("Sim time: %lf", payload.time);
    //ImGui::Text("North-South position: %lf", payload.north);
    //ImGui::Text("East-West position: %lf", payload.east);
    ImGui::Text("Altitude (ft): %lf", payload.up);
    ImGui::Text("Heading (deg): %lf", payload.heading);
    ImGui::Text("Airspeed (kts): %lf", payload.airspeed);
    ImGui::Text("Throttle (%): %lf", payload.throttle);
    ImGui::Text("Rpm: %lf", payload.rpm);
    ImGui::Text("Pitch (deg): %lf", payload.pitch);
    ImGui::Text("Roll (deg): %lf", payload.roll);
    ImGui::Text("Brake: %s", payload.brake ? "on" : "off");

    ImGui::End();
    ImGui::Render();
}

void Window::renderGraphics(RendererPayload& payload) const {
    renderer_->render(payload);
}
