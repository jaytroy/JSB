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
        name = SDL_JoystickName(joystick_);
    }
    SDL_JoystickEventState(SDL_ENABLE);

    std::cout << "Registered joystick " << name;
}

bool Joystick::pollEvents(InputEvent &outEvent) {
    //This should be unnecessary.
    //An event simply existing should indicate an activation.
    bool activated = false;

    SDL_Event sdlEvent;

    while (SDL_PollEvent(&sdlEvent)) {
        if (sdlEvent.type == SDL_JOYAXISMOTION) {
            outEvent.type = JOYAXIS;

            Uint8 axis = sdlEvent.jaxis.axis;
            Sint16 value = sdlEvent.jaxis.value; // 2^16 / 2 denotes max movement (32768)

            switch (axis) {
                case 0:
                    //Roll
                    outEvent.info = 0;
                    break;
                case 1:
                    //Pitch
                    outEvent.info = 1;
                    break;
                case 2:
                    //Yaw
                    outEvent.info = 2;
                    break;
                case 3:
                    //Slider
                    outEvent.info = 3;
                default:
                    throw std::runtime_error("Bad axis");

                    //Clamp axes from -1.0 to 1.0
                    value /= 32768;
                    outEvent.delta = value;

                    activated = true;
            }
        } else if (sdlEvent.type == SDL_JOYBUTTONDOWN) {
            activated = true;
            outEvent.type = JOYBTN;

            Uint8 btn = sdlEvent.jbutton.button;
            outEvent.delta = btn;
        } else {
            throw std::runtime_error(std::format("Unrecognized joystick input from {}", name));
        }

    }

    return activated;
}
