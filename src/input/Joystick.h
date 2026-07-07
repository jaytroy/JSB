//
// Created by jay on 7/2/26.
//

#ifndef JSB_JOYSTICK_H
#define JSB_JOYSTICK_H
#include <SDL_joystick.h>
#include <string>

#include "../model/input/InputDevice.h"

class Joystick : public InputDevice {
public:
    Joystick();
    bool pollEvents(InputEvent &outEvent) override;
    enum class Motion { PITCH, ROLL, YAW, SLIDER };

private:
    SDL_Joystick *joystick_;
    std::string name;
};


#endif //JSB_JOYSTICK_H
