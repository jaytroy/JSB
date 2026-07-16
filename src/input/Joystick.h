//
// Created by jay on 7/2/26.
//

#ifndef JSB_JOYSTICK_H
#define JSB_JOYSTICK_H
#include <SDL_joystick.h>

#include "../shared/AxisDevice.hpp"
#include "../SDL/EventSink.h"
#include "ControlBinding.h"

//Make this a struct?


class Joystick : public AxisDevice, public EventSink {
public:
    explicit Joystick(int deviceIndex);

    void sampleState(std::vector<OutCommand> &outCommands) override;
    void onEvent(const SDL_Event& out) override;

    void createControlBinding(const char *name);
    void updateBinding(std::pair<int, std::string>, const std::string &);

    void debugControls() const;

private:
    SDL_Joystick *joystick_;

    ControlBinding c_;
};


#endif //JSB_JOYSTICK_H
