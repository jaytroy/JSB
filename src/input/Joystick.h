//
// Created by jay on 7/2/26.
//

#ifndef JSB_JOYSTICK_H
#define JSB_JOYSTICK_H
#include <SDL_joystick.h>
#include <string>

#include "../simulation/input/AxisDevice.h"
#include "../SDL/EventSink.h"

class Joystick : public AxisDevice, public EventSink {
public:
    Joystick();
    void sampleState(ControlEvent& out) override;
    void onEvent(const SDL_Event& out) override;

private:
    SDL_Joystick *joystick_;
    std::string name;
};


#endif //JSB_JOYSTICK_H
