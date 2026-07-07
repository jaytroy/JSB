//
// Created by jay on 7/2/26.
//

#include "Joystick.h"

#include <format>
#include <iostream>
#include <ncurses.h>
#include <SDL.h>
#include <SDL_events.h>
#include <string>

Joystick::Joystick() {
    SDL_Init(SDL_INIT_JOYSTICK);

    joystick_ = SDL_JoystickOpen(0);
    if (!joystick_) {
        throw std::runtime_error("No joystick found");
    }
    name = SDL_JoystickName(joystick_);
    SDL_JoystickEventState(SDL_ENABLE);

    std::cout << "Registered joystick " << name;
}

void Joystick::sampleState(InputEvent &outEvent) {

    double pitch, roll, yaw, slider;
    roll = SDL_JoystickGetAxis(joystick_, 0);
    pitch = SDL_JoystickGetAxis(joystick_, 1);
    yaw = SDL_JoystickGetAxis(joystick_, 2);
    slider = SDL_JoystickGetAxis(joystick_, 3);


    // 2^16 / 2 denotes max movement (32768)
    //Clamp axes from -1.0 to 1.0
    roll /= 32768;
    pitch /= 32768;
    yaw /= 32768;
}

void Joystick::onEvent(InputEvent &out) {

}

