//
// Created by jay on 7/2/26.
//

#include "Joystick.h"

#include <algorithm>
#include <format>
#include <fstream>
#include <iostream>
#include <SDL.h>
#include <SDL_events.h>
#include <string>

#include "../../external/json.hpp"
#include "ControlBinding.h"
#include "../shared/FcsCommand.h"

Joystick::Joystick(const int deviceIndex) {
    joystick_ = SDL_JoystickOpen(deviceIndex);
    if (!joystick_) {
        throw std::runtime_error(std::format("Joystick device {} not found", deviceIndex));
    }
    const char* name = SDL_JoystickName(joystick_);
    SDL_JoystickEventState(SDL_ENABLE);

    createControlBinding(name);

    std::cout << "Registered joystick " << name << std::endl;
}

Joystick::~Joystick() {
    SDL_JoystickClose(joystick_);
}

static double hatAngle(const Uint8 value) {
    switch (value) {
        case SDL_HAT_UP:        return 0.0;
        case SDL_HAT_RIGHTUP:   return 45.0;
        case SDL_HAT_RIGHT:     return 90.0;
        case SDL_HAT_RIGHTDOWN: return 135.0;
        case SDL_HAT_DOWN:      return 180.0;
        case SDL_HAT_LEFTDOWN:  return 225.0;
        case SDL_HAT_LEFT:      return 270.0;
        case SDL_HAT_LEFTUP:    return 315.0;
        default: throw std::runtime_error("Unknown hat value");
    }
}

void Joystick::sampleState(std::vector<OutCommand>& outCommands) {
    //debugControls();

    for (const auto& [index, action, inverted, type] : c_.axes) {
        OutCommand out;
        out.command = fromString(action);
        if (out.command != FcsCommand::None) { //Filter out dead binds
            out.type = Continuous;
            out.value = normalize(inverted * SDL_JoystickGetAxis(joystick_, index), type);

            outCommands.push_back(out);
        }
    }

    for (const auto& [index, action, inverted, type] : c_.hats) {
        const Uint8 value = SDL_JoystickGetHat(joystick_, index);
        if (value == SDL_HAT_CENTERED) continue;

        OutCommand out;
        out.command = fromString(action);
        if (out.command != FcsCommand::None) {
            out.type = Discrete;
            out.value = hatAngle(value);

            outCommands.push_back(out);
        }
    }
}

void Joystick::onEvent(SDL_Event& event) {
    if (event.type != SDL_JOYBUTTONDOWN) return;

    pending_.push_back(event);
}

void Joystick::drain(std::vector<OutCommand> &outCommands) {
    for (const SDL_Event& event : pending_) {
        const auto it = std::find_if(c_.buttons.begin(), c_.buttons.end(),
            [&](const Control& b) { return b.index == event.jbutton.button; });
        if (it == c_.buttons.end()) continue;

        OutCommand out;
        out.command = fromString(it->action);
        if (out.command != FcsCommand::None) {
            out.type = Discrete;
            outCommands.push_back(out);
        }
    }

    pending_.clear();
}


//These can likely be moved out into its own json class.
/**
 * This reads a control binding and creates a data struct that allows for data to be passed forward.
 * @param name The name of the file containing the bindings.
 */
void Joystick::createControlBinding(const char* name) {
    const std::string configPath = std::format(SRC_DIR "input/configs/{}.json", name);
    try {
        std::ifstream file(configPath, std::ifstream::in);
        c_ = nlohmann::json::parse(file).get<ControlBinding>();
    } catch (nlohmann::detail::exception& e) {
        throw std::runtime_error(
            std::format("Failed to parse json config {}\n"
                        "Details: {}\n"
                        "\033[33mAre you sure the config {} is correct?\033[0m",
            configPath, e.what(), name));
    }
}

//TODO: Dynamic bindings
void Joystick::updateBinding(const std::pair<int, std::string>, const std::string &newBinding) {
    std::string configPath = std::format(SRC_DIR "input/configs/{}.json", c_.device);
}

/**
 * Prints all the axes and their current values into stdout.
 */
void Joystick::debugAxes() const {
    for (int i = 0; i < 16; i++) {
        std::cout << "Axis " << i << ": " << SDL_JoystickGetAxis(joystick_, i) << std::endl;
        //std::cout << "Hat " << i << SDL_JoystickGetHat(joystick_, i) << endl;
        //<std::cout << "Button " << i << SDL_JoystickGetButton(joystick_, i) << endl;
    }
}
