//
// Created by jay on 7/13/26.
//

#ifndef JSB_INPUTDEVICEFACTORY_H
#define JSB_INPUTDEVICEFACTORY_H
#include <functional>
#include <iostream>
#include <memory>
#include <SDL.h>
#include <SDL_joystick.h>

#include "../shared/AxisDevice.hpp"
#include "Joystick.h"

/**
 * Enables easy and decoupled creation of input devices;
 */
class InputDeviceFactory {
    //This is currently moreso JoystickFactory. Should be refactored.
public:
    using Creator = std::function<std::unique_ptr<AxisDevice>()>;

    static std::vector<std::unique_ptr<AxisDevice>> createAxisDevices() {
        SDL_Init(SDL_INIT_JOYSTICK);
        const int totalJoysticks = SDL_NumJoysticks();
        std::cout << "Found " << totalJoysticks << " joysticks" << std::endl;
        std::unordered_map<int, Creator> registry{};

        //This should be implementation agnostic
        //Abstract factory pattern?
        //TODO: Verify that AxisDevice will be implemented on more things
        //Is ID even necesary? I don't think so. Moving away from it
        for (int i = 0; i < totalJoysticks; i++) {
            try {
                registry[i] = { [i] { return std::make_unique<Joystick>(i); }};
            } catch (std::exception &e) {
                std::cout << "Failed to initialize joystick: " << i << std::endl;
            }
        }

        std::vector<std::unique_ptr<AxisDevice>> result;
        for (auto& [index, creator] : registry) {
            result.push_back(creator());
        }

        return result;
    }
};


#endif //JSB_INPUTDEVICEFACTORY_H
