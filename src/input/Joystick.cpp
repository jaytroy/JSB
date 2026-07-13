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

Joystick::Joystick(const int deviceIndex) {
    SDL_Init(SDL_INIT_JOYSTICK);

    joystick_ = SDL_JoystickOpen(deviceIndex);
    if (!joystick_) {
        throw std::runtime_error(std::format("Joystick device {} not found", deviceIndex));
    }
    name_ = SDL_JoystickName(joystick_);
    SDL_JoystickEventState(SDL_ENABLE);

    std::cout << "Registered joystick " << name_;
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

void Joystick::createControlBlock() {
    nlohmann::json data;
    std::ifstream file(std::format("{}.json", name_), std::ifstream::in);
    file >> data;
    //std::vector<object>
    nlohmann::json jf = nlohmann::json::parse(file);

    numAxes = 0;
    numHats = 0;
    numButtons = 0;
    for (numAxes) {

    }

    for (numHats) {
    }

    for (numButtons) {
    }

    //Read from json:
    //read_file(name)
    //Init axes
    //Init hats
    //Init buttons
}
