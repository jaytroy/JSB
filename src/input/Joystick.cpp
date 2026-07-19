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
}

void Joystick::onEvent(SDL_Event& event) {
    if (event.type != SDL_JOYHATMOTION && event.type != SDL_JOYBUTTONDOWN) return;

    pending_.push_back(event);
}

void Joystick::drain(std::vector<OutCommand> &outCommands) {
    //Don't like SDL_Event here directly
    for (SDL_Event event : pending_) {
        if (event.type == SDL_JOYHATMOTION) {
            Uint8 index = event.jhat.hat;

            OutCommand out;
            //Should this be here?
            Control control = c_.hats.at(index);
            out.command = fromString(control.action);
            if (out.command != FcsCommand::None) {
                out.value = event.jhat.value;
                out.type = Discrete;
                outCommands.push_back(out);
            }
        } else if (event.type == SDL_JOYBUTTONDOWN) {
            Uint8 index = event.jbutton.button;

            OutCommand out;
            Control control = c_.buttons.at(index);
            out.command = fromString(control.action);
            if (out.command != FcsCommand::None) {
                out.type = Discrete;
                outCommands.push_back(out);
            }
        } else {
            //I don't know how this could even be reached, but it's here for safety
            //Maybe if a random photon hits the gpu fan
            throw std::runtime_error("Unknown joystick onEvent trigger");
        }

        for (const auto& [index, action, inverted, type] : c_.buttons) {
            OutCommand out;
            out.command = fromString(action);
            if (out.command != FcsCommand::None) {
                out.type = Discrete;
                out.value = SDL_JoystickGetHat(joystick_, index);

                outCommands.push_back(out);
            }
        }
    }
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

void Joystick::updateBinding(const std::pair<int, std::string>, const std::string &newBinding) {
    std::string configPath = std::format(SRC_DIR "input/configs/{}.json", c_.device);
}

void Joystick::debugAxes() const {
    for (int i = 0; i < 16; i++) {
        std::cout << "Axis " << i << ": " << SDL_JoystickGetAxis(joystick_, i) << std::endl;
        //std::cout << "Hat " << i << SDL_JoystickGetHat(joystick_, i) << endl;
        //<std::cout << "Button " << i << SDL_JoystickGetButton(joystick_, i) << endl;
    }
}
