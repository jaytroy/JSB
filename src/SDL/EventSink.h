//
// Created by jay on 7/7/26.
//

#ifndef JSB_EVENTSINK_H
#define JSB_EVENTSINK_H
#include <SDL2/SDL_events.h>
#include <shared/FcsCommand.h> //I'm not a big fan of this here. Refactor?

/**
 * Defines functionality for discrete events like mouse, keyboard.
 * Events here are taken directly from an event pump.
 */
class EventSink {
public:
    virtual ~EventSink() = default;
    virtual void onEvent(SDL_Event& event) = 0;
    virtual void drain(std::vector<OutCommand> &outCommands) {}
};

#endif //JSB_EVENTSINK_H
