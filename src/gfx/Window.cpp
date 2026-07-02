//
// Created by jay on 7/2/26.
//

#include "Window.h"

#include <SDL.h>
#include <stdexcept>

Window::Window() {
    int w, h, bpp, flags;

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        throw std::runtime_error("Video init failed");
    }

    SDL_Window* window = SDL_CreateWindow("SDL3 OpenGl test");

    SDL_DisplayMode info;
    SDL_GetDesktopDisplayMode(0, &info);

    w = 640;
    h = 480;
    bpp = info->vmft

}
