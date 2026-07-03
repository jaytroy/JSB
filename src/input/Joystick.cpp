//
// Created by jay on 7/2/26.
//

#include "Joystick.h"

#include <iostream>
#include <SDL.h>
#include <SDL_events.h>
#include <string>

bool Joystick::pollEvents(std::vector<InputEvent> &outEvent) {
    SDL_Init(SDL_INIT_JOYSTICK);

    SDL_Joystick *joystick = SDL_JoystickOpen(0);
    std::string name = SDL_JoystickName(joystick);
   // std::cout << name;

    bool activated = false;

    SDL_Event sdlEvent;
    int axis, value, pitch, roll, yaw, slider;
    while (SDL_PollEvent(&sdlEvent)) {
        if (sdlEvent.type == SDL_JOYAXISMOTION) {
            axis = sdlEvent.jaxis.axis;
            value = sdlEvent.jaxis.value; //max val is 32768 for T16000.M
            switch (axis) {
                case 0:
                    roll = value;
                    break;
                case 1:
                    pitch = value;
                    break;
                case 2:
                    yaw = value;
                    break;
                case 3:
                    slider = value;
                default:
                    throw std::runtime_error("Bad axis");
            }

            //Clamp axes -1.0 to 1.0
            pitch = (double) pitch / 32768;
            roll = (double) roll / 32768;
            yaw = (double) yaw / 32768;
            slider = (double) slider / 32768;

            //std::cout << "Pitch" << pitch << "   roll" << roll << "\n";

            InputEvent event;
            event.pitch = pitch;
            event.roll = roll;
            event.yaw = yaw;
            event.keyCode = -10;

            outEvent.push_back(event);

            activated = true;
            //std::cout << "Axis" << axis << "   value" << value << "\n";
        }
    }



    return activated;
}
