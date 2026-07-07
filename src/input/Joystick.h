//
// Created by jay on 7/2/26.
//

#ifndef JSB_JOYSTICK_H
#define JSB_JOYSTICK_H
#include <string>

#include "../model/input/InputDevice.h"
#include "../model/input/EventSink.h"

class Joystick : public InputDevice, public EventSink {
public:
    Joystick();
    void sampleState(InputEvent& out) override;

    void onEvent(InputEvent& out) override;

    enum class Motion { PITCH, ROLL, YAW, SLIDER };

private:
    SDL_Joystick *joystick_;
    std::string name;
};


#endif //JSB_JOYSTICK_H
