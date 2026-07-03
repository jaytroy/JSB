//
// Created by jay on 7/2/26.
//

#ifndef JSB_JOYSTICK_H
#define JSB_JOYSTICK_H
#include <SDL_joystick.h>
#include <vector>

#include "InputDevice.h"


class Joystick : public InputDevice {
public:
    Joystick();
    bool pollEvents(std::vector<InputEvent> &outEvent) override;

private:
    SDL_Joystick *joystick_;
};


#endif //JSB_JOYSTICK_H
