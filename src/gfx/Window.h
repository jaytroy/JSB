//
// Created by jay on 7/2/26.
//

#ifndef JSB_WINDOW_H
#define JSB_WINDOW_H
#include <memory>
#include <SDL_video.h>
#include <vector>

#include "GfxEventSink.h"
#include "GLRenderer.h"
#include "SDL/EventSink.h"
#include "networking/UdpServer.hpp"
#include "shared/RendererPayload.hpp"

class Window {
public:
    Window();

    ~Window();

    void renderFrame(RendererPayload& payload);

    EventSink* getGfxSink() { return &gfxSink_; }

private:
    void renderGUI(const RendererPayload &payload);
    void renderGraphics(RendererPayload &payload) const;

    const int WINDOW_WIDTH = 800;
    const int WINDOW_HEIGHT = 600;
    const SDL_Color BG_COLOR = { 0, 0, 255, 255 };

    SDL_Window* window_ = nullptr;
    std::unique_ptr<GLRenderer> renderer_;
    SDL_GLContext gl_;

    GfxEventSink gfxSink_;
    UdpServer server_;
};

#endif //JSB_WINDOW_H
