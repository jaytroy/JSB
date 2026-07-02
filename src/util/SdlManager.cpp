//
// Created by jay on 7/1/26.
//

#include "SdlManager.h"

#include <vector>

bool SdlManager::pollEvents(std::vector<InputEvent> &outEvent) {

    SDL_Event sdlEvent;
    std::vector<InputEvent> inputEvents;
    while (SDL_PollEvent(&sdlEvent)) {

        if (sdlEvent.type == SDL_KEYDOWN || sdlEvent.type == SDL_KEYUP) {
            SDL_KeyboardEvent keyEvent = sdlEvent.key;
            InputEvent event;
            event.code = keyEvent.keysym.sym;
            inputEvents.push_back(event);
        }
    }

    return true;
}
