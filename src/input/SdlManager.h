//
// Created by jay on 7/1/26.
//

#include <vector>
#include <SDL2/SDL.h>

#include "../model/input/InputDevice.h"

#ifndef JSB_SDLMANAGER_H
#define JSB_SDLMANAGER_H


/**
 * Depracted? This is meant to handle keyboard input. Can likely turn it all into a single eventqueue.
 */
class SdlManager : public InputDevice {
public:
    bool pollEvents(InputEvent &outEvent) override;
};


#endif //JSB_SDLMANAGER_H
