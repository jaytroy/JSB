//
// Created by jay on 7/7/26.
//

#ifndef JSB_KEYBOARDSINK_H
#define JSB_KEYBOARDSINK_H
#include "../SDL/EventSink.h"
#include <SDL2/SDL_events.h>
#include <vector>
#include <unordered_map>

#include "../model/fcs/FcsCommand.h"


class KeyboardSink : public EventSink {
public:
    void onEvent(const SDL_Event& event) override {
        if (event.type != SDL_KEYDOWN) return;

        auto it = keyToCommand_.find(event.key.keysym.sym);
        if (it != keyToCommand_.end())
            pending_.push_back(it->second);
    }

    void drain(std::vector<FcsCommand>& out) {
        out.swap(pending_);
        pending_.clear();
    }

private:
    std::vector<FcsCommand> pending_;

    std::unordered_map<SDL_Keycode, FcsCommand> keyToCommand_ = {
        {SDLK_w, FcsCommand::PitchDown},   {SDLK_s, FcsCommand::PitchUp},
        {SDLK_a, FcsCommand::RollLeft},    {SDLK_d, FcsCommand::RollRight},
        {SDLK_q, FcsCommand::YawLeft},     {SDLK_e, FcsCommand::YawRight},
        {SDLK_u, FcsCommand::ThrottleUp},  {SDLK_n, FcsCommand::ThrottleDown},
        {SDLK_b, FcsCommand::ToggleBrake}, {SDLK_p, FcsCommand::ToggleEngine},
    };
};
#endif //JSB_KEYBOARDSINK_H
