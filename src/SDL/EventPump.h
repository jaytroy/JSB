//
// Created by jay on 7/7/26.
//

#ifndef JSB_EVENTPUMP_H
#define JSB_EVENTPUMP_H
#include <vector>
#include <SDL2/SDL_events.h>
#include "EventSink.h"

/**
 * Pumps SDL events from the event queue.
 */
class EventPump {
public:
    void addSink(EventSink *sink) { sinks_.push_back(sink); }

    /**
     * Pumps events, return false if QUIT signal is sent.
     * @return
     */
    bool pump() {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT)
                return false;
            for (EventSink *sink: sinks_) {
                sink->onEvent(event); //Perform respective logic for each event
            }
        }
        return true; 
    }

private:
    std::vector<EventSink *> sinks_;
};

#endif //JSB_EVENTPUMP_H
