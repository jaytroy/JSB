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

void Joystick::onEvent(const SDL_Event &out) {
    OutCommand out1;
    out1.command = FcsCommand::None;
    out1.type = Discrete;
    out1.value = -1;

    //nada
    //This will be similar to above.
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

void Joystick::debugControls() const {
    for (int i = 0; i < 16; i++) {
        std::cout << "Axis " << i << ": " << SDL_JoystickGetAxis(joystick_, i) << std::endl;
        //std::cout << "Hat " << i << SDL_JoystickGetHat(joystick_, i) << endl;
        //<std::cout << "Button " << i << SDL_JoystickGetButton(joystick_, i) << endl;
    }
}
