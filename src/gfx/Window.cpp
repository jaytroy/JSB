//
// Created by jay on 7/2/26.
//

#include "Window.h"

#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_sdlrenderer2.h"

#include <SDL.h>
#include <stdexcept>

Window::Window() { //Give it an abstract implementation
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        throw std::runtime_error("SDL video init failed");
    }

    window_ = SDL_CreateWindow("SDL3 OpenGl test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    if (!window_) {
        SDL_Quit();
        throw std::runtime_error("SDL window init failed");
    }

    renderer_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer_) {
        SDL_DestroyWindow(window_);
        SDL_Quit();
        throw std::runtime_error("SDL renderer init failed");
    }

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.FontGlobalScale = 1.5f;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

    ImGui::StyleColorsDark();
    ImGui::GetStyle().ScaleAllSizes(1.5f);

    ImGui_ImplSDL2_InitForSDLRenderer(window_, renderer_);
    ImGui_ImplSDLRenderer2_Init(renderer_);
}

void Window::cleanup() {
    ImGui_ImplSDLRenderer2_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();

    SDL_DestroyRenderer(renderer_);
    SDL_DestroyWindow(window_);
    SDL_Quit();
}

void Window::renderFrame(std::vector<double>& payload) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        ImGui_ImplSDL2_ProcessEvent(&event); //This needs to be somewhere where it makes sense
    }

    renderGraphics();
    renderGUI(payload);

    SDL_SetRenderDrawColor(renderer_, BG_COLOR.r, BG_COLOR.g, BG_COLOR.b, BG_COLOR.a);
    SDL_RenderClear(renderer_);

    ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData(), renderer_);
    SDL_RenderPresent(renderer_);
}

void Window::renderGUI(std::vector<double> &payload) {
    ImGui_ImplSDLRenderer2_NewFrame();
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

void Window::renderGraphics() {
    // TODO: OpenGL rendering
}
