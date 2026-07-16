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
    void onEvent(const SDL_Event &event) override {
        if (event.type != SDL_KEYDOWN) return;

        pending_.push_back(event.key.keysym.sym);
    }

    void drain(std::vector<OutCommand> &outCommands) {
        for (int key: pending_) {
            OutCommand out;
            out.first = fromKey(key);
            out.second = -1;
            outCommands.push_back(out);
        }

        pending_.clear();
    }

private:
    std::vector<int> pending_;

    //Merge this with FcsCommand::fromString? I don't like it here.
    static FcsCommand fromKey(const int c) {
        static std::unordered_map<int, FcsCommand> registry = {
            {'w', FcsCommand::PitchDown},
            {'s', FcsCommand::PitchUp},
            {'a', FcsCommand::RollLeft},
            {'d', FcsCommand::RollRight},
            {'q', FcsCommand::YawLeft},
            {'e', FcsCommand::YawRight},
            {'u', FcsCommand::ThrottleUp},
            {'n', FcsCommand::ThrottleDown},
            {'b', FcsCommand::ToggleBrake},
            {'p', FcsCommand::ToggleEngine}
        };

        auto out = registry.find(c);
        return out != registry.end() ? out->second : FcsCommand::None;
    }
};




#endif //JSB_KEYBOARDSINK_H
