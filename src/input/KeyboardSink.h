//
// Created by jay on 7/7/26.
//

#ifndef JSB_KEYBOARDSINK_H
#define JSB_KEYBOARDSINK_H

#include "../SDL/EventSink.h"
#include <SDL2/SDL_events.h>
#include <vector>

class KeyboardSink : public EventSink {
public:
    void onEvent(const SDL_Event& event) override {
        if (event.type != SDL_KEYDOWN) return;

        pending_.push_back(event.key.keysym.sym);
    }

    std::vector<int> drain() {
        std::vector<int> out;
        out.swap(pending_);
        pending_.clear();
        return out;
    }

private:
    std::vector<int> pending_;

};
#endif //JSB_KEYBOARDSINK_H
