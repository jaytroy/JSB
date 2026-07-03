//
// Created by jay on 7/2/26.
//

#include "Joystick.h"

#include <iostream>
#include <ncurses.h>
#include <SDL.h>
#include <SDL_events.h>
#include <string>

Joystick::Joystick() {
    SDL_Init(SDL_INIT_JOYSTICK);

    joystick_ = SDL_JoystickOpen(0);
    std::string name = SDL_JoystickName(joystick_);
    if (!joystick_) {
        throw std::runtime_error("Failed to get joystick");
    }
    SDL_JoystickEventState(SDL_ENABLE);

    //std::cout << name;
}

bool Joystick::pollEvents(std::vector<InputEvent> &outEvent) {
    bool activated = false;

    SDL_Event sdlEvent;
    int axis = 0;
    double value = 0;
    InputEvent event;
    while (SDL_PollEvent(&sdlEvent)) {
        if (sdlEvent.type == SDL_JOYAXISMOTION) {
            axis = sdlEvent.jaxis.axis;
            value = sdlEvent.jaxis.value; //max val is 32768 for T16000.M
            switch (axis) {
                case 0:
                    //Roll
                    event.type = 0;
                    break;
                case 1:
                    //Pitch
                    event.type = 1;
                    break;
                case 2:
                    //Yaw
                    event.type = 2;
                    break;
                case 3:
                    event.type = 3;
                default:
                    throw std::runtime_error("Bad axis");
            }

            //Clamp axes -1.0 to 1.0
            value /= 32768;

            //std::cout << "Pitch" << pitch << "   roll" << roll << "\n";

            event.delta = value;
            event.keyCode = -10;

            outEvent.push_back(event);

            activated = true;
            //std::cout << "Axis" << axis << "   value" << value << "\n";
        }
    }



    return activated;
}
