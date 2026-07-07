//
// Created by jay on 7/2/26.
//

#ifndef JSB_WINDOW_H
#define JSB_WINDOW_H
#include <SDL_render.h>
#include <SDL_video.h>


class Window {
public:
    Window();
    void cleanup();
    void renderFrame(double time, double airspeed, double posN, double posE, double posU, double rpm, double heading, double brake, double
                     roll, double throttle, double
                     pitch);
    void loop();

private:
    const int WINDOW_WIDTH = 800;
    const int WINDOW_HEIGHT = 600;
    const SDL_Color BG_COLOR = { 0, 0, 255, 255 };

    int bpp, flags;

    SDL_Window* window_ = nullptr;
    SDL_Renderer* renderer_ = nullptr;
};

#endif //JSB_WINDOW_H
