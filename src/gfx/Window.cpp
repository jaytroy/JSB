//
// Created by jay on 7/2/26.
//

#include "Window.h"

#include <SDL.h>
#include <stdexcept>



Window::Window() {
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
}

void Window::cleanup() {
    SDL_DestroyRenderer(renderer_);
    SDL_DestroyWindow(window_);
    SDL_Quit();
}

void Window::renderFrame() {
    SDL_SetRenderDrawColor(renderer_, BG_COLOR.r, BG_COLOR.g, BG_COLOR.b, BG_COLOR.a);
    SDL_RenderClear(renderer_);
    SDL_RenderPresent(renderer_);
}
