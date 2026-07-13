//
// Created by jay on 7/2/26.
//

#include "Joystick.h"

#include <format>
#include <iostream>
#include <SDL.h>
#include <SDL_events.h>
#include <string>

Joystick::Joystick(const int deviceIndex) {
    SDL_Init(SDL_INIT_JOYSTICK);

    joystick_ = SDL_JoystickOpen(deviceIndex);
    if (!joystick_) {
        throw std::runtime_error("No joystick found");
    }
    name = SDL_JoystickName(joystick_);
    SDL_JoystickEventState(SDL_ENABLE);

    std::cout << "Registered joystick " << name;
}

void Joystick::sampleState(ControlEvent &outEvent) {

    double pitch, roll, yaw, slider;
    //Axes need to be inverted to transfer into what joystick controls should be
    roll = normalize(-SDL_JoystickGetAxis(joystick_, 0));
    pitch = normalize(-SDL_JoystickGetAxis(joystick_, 1));
    yaw = normalize(-SDL_JoystickGetAxis(joystick_, 2));
    slider = normalize(32767.0f - SDL_JoystickGetAxis(joystick_, 3)) * 2;

    outEvent.roll = roll;
    outEvent.pitch = pitch;
    outEvent.yaw = yaw;
    outEvent.slider = slider;
}

void Joystick::onEvent(const SDL_Event &out) {
    //nada
}