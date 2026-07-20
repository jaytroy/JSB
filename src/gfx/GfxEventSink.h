//
// Created by jay on 7/7/26.
//

#ifndef JSB_GFXEVENTSYNC_H
#define JSB_GFXEVENTSYNC_H

#include "imgui_impl_sdl2.h"

#include "../SDL/EventSink.h"

/**
 * Processes input events on the window.
 * Right now, specifically, the GUI.
 */
class GfxEventSink : public EventSink {
public:
    void onEvent(SDL_Event& event) override {
        ImGui_ImplSDL2_ProcessEvent(&event);
    }
};

#endif //JSB_GFXEVENTSYNC_H
