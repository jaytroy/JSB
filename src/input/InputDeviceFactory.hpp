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

#include "../data/AxisDevice.hpp"
#include "Joystick.h"

/**
 * Enables easy and decoupled creation of input devices;
 */
class InputDeviceFactory {
public:
    using Creator = std::function<std::unique_ptr<AxisDevice>()>;

    static std::unordered_map<int, std::unique_ptr<AxisDevice>> createAll() {
        SDL_Init(SDL_INIT_JOYSTICK);
        const int totalJoysticks = SDL_NumJoysticks();
        std::cout << "Found " << totalJoysticks << " joysticks" << std::endl;
        static std::unordered_map<int, Creator> registry{};

        //This should be implementation agnostic
        //Abstract factory pattern?
        //TODO: Verify that AxisDevice will be implemented on more things
        for (int i = 0; i < totalJoysticks; i++) {
            registry[i] = { [i] { return std::make_unique<Joystick>(i); }};
        }

        std::unordered_map<int, std::unique_ptr<AxisDevice>> result;
        for (auto& [index, creator] : registry) {
            result[index] = creator();
        }

        return result;
    }


private:
    std::vector<std::pair<int, std::unique_ptr<AxisDevice>>> devices_;
};


#endif //JSB_INPUTDEVICEFACTORY_H
