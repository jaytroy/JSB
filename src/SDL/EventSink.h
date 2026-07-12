//
// Created by jay on 7/7/26.
//

#ifndef JSB_EVENTSINK_H
#define JSB_EVENTSINK_H
#include "imgui_impl_sdl2.h"

/**
 * Defines functionality for discrete events like mouse, keyboard.
 * Events here are taken directly from an event pump.
 */
class EventSink {
public:
    virtual ~EventSink() = default;
    virtual void onEvent(const SDL_Event& out) = 0;
};

#endif //JSB_EVENTSINK_H
