//
// Created by jay on 7/2/26.
//

#ifndef JSB_JOYSTICK_H
#define JSB_JOYSTICK_H
#include <vector>

#include "InputDevice.h"


class Joystick : public InputDevice {
public:
    bool pollEvents(std::vector<InputEvent> &outEvent) override;
};


#endif //JSB_JOYSTICK_H
