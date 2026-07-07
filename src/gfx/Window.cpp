//
// Created by jay on 7/2/26.
//

#include "Window.h"

#include <iostream>

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

void Window::renderFrame(double time, double airspeed, double posN, double posE, double posU, double rpm, double heading, double brake, double roll, double throttle, double pitch) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        ImGui_ImplSDL2_ProcessEvent(&event); //This needs to be somewhere where it makes sense
    }

    //Frame start
    ImGui_ImplSDLRenderer2_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();

    ImGui::SetNextWindowSize(ImVec2(500, 5  00), ImGuiCond_FirstUseEver);
    ImGui::Begin("Flight controls");
    ImGui::Text("Sim time: %lf", time);
    ImGui::Text("North-South position: %lf", posN);
    ImGui::Text("East-West position: %lf", posE);
    ImGui::Text("Up-Down position: %lf", posU);
    ImGui::Text("Heading: %lf", heading);
    ImGui::Text("Airspeed: %lf", airspeed);
    ImGui::Text("Throttle: %lf", throttle);
    ImGui::Text("Rpm: %lf", rpm);
    ImGui::Text("Pitch: %lf", pitch);
    ImGui::Text("Roll: %lf", roll);
    ImGui::Text("Brake: %lf", brake);

    ImGui::End();
    ImGui::Render();

    SDL_SetRenderDrawColor(renderer_, BG_COLOR.r, BG_COLOR.g, BG_COLOR.b, BG_COLOR.a);
    SDL_RenderClear(renderer_);

    ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData(), renderer_);
    SDL_RenderPresent(renderer_);
}
