//
// Created by jay on 7/1/26.
//

#include "SdlManager.h"

#include <vector>

bool SdlManager::pollEvents(std::vector<InputEvent> &outEvent) {

    SDL_Event sdlEvent;
    std::vector<InputEvent> inputEvents;

    bool activated = false;
    while (SDL_PollEvent(&sdlEvent)) {

        if (sdlEvent.type == SDL_KEYDOWN || sdlEvent.type == SDL_KEYUP) {
            SDL_KeyboardEvent keyEvent = sdlEvent.key;
            InputEvent event;
            event.keyCode = keyEvent.keysym.sym;
            outEvent.push_back(event);
            activated = true;
        }
    }
    return activated;
}
