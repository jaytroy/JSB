//
// Created by jay on 7/2/26.
//

#ifndef JSB_JOYSTICK_H
#define JSB_JOYSTICK_H
#include <SDL_joystick.h>
#include <string>
#include <unordered_map>

#include "AxisDevice.h"
#include "../SDL/EventSink.h"

//Make this a struct?
typedef std::vector<std::tuple<std::unordered_map<int, char*>, double>> ControlBlock;


class Joystick : public AxisDevice, public EventSink {
public:
    explicit Joystick(int deviceIndex);
    void sampleState(ControlEvent &outEvent) override;
    void onEvent(const SDL_Event& out) override;

    void createControlBlock();

private:
    SDL_Joystick *joystick_;
    std::string name_;

    ControlBlock axes_;
    ControlBlock hats_;
    ControlBlock buttons_;
};


#endif //JSB_JOYSTICK_H
