//
// Created by jay on 7/2/26.
//

#include "Joystick.h"

#include <format>
#include <fstream>
#include <iostream>
#include <SDL.h>
#include <SDL_events.h>
#include <string>

#include "json.hpp"
#include "ControlBinding.h"

Joystick::Joystick(const int deviceIndex) {
    SDL_Init(SDL_INIT_JOYSTICK);

    joystick_ = SDL_JoystickOpen(deviceIndex);
    if (!joystick_) {
        throw std::runtime_error(std::format("Joystick device {} not found", deviceIndex));
    }
    const char* name = SDL_JoystickName(joystick_);
    SDL_JoystickEventState(SDL_ENABLE);

    createControlBinding(name);

    std::cout << "Registered joystick " << name << std::endl;
}

void Joystick::sampleState(ControlEvent &outEvent) {
    //debugControls();

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

void Joystick::createControlBinding(const char* name) {
    std::string configPath = std::format(SRC_DIR "input/configs/{}.json", name);
    try {
        std::ifstream file(configPath, std::ifstream::in);
        c_ = nlohmann::json::parse(file).get<ControlBinding>();
    } catch (nlohmann::detail::exception& e) {
        std::cout << "Failed to parse json config " << configPath << "\nDetails: " << e.what() << std::endl;
    }
}

void Joystick::debugControls() const {
    for (int i = 0; i < 16; i++) {
        std::cout << "Axis " << i << ": " << SDL_JoystickGetAxis(joystick_, i) << std::endl;
        //std::cout << "Hat " << i << SDL_JoystickGetHat(joystick_, i) << endl;
        //<std::cout << "Button " << i << SDL_JoystickGetButton(joystick_, i) << endl;
    }
}
