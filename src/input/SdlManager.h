//
// Created by jay on 7/1/26.
//

#include <vector>
#include <SDL2/SDL.h>

#include "InputDevice.h"

#ifndef JSB_SDLMANAGER_H
#define JSB_SDLMANAGER_H


class SdlManager : public InputDevice {
public:
    bool pollEvents(std::vector<InputEvent> &outEvent) override;
};


#endif //JSB_SDLMANAGER_H
