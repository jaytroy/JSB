//
// Created by jay on 7/7/26.
//

#include "InputHandler.h"

#include <FGFDMExec.h>

#include "InputDevice.h"
#include "../../input/Joystick.h"
#include "../fcs/FcsStrategyFactory.h"

InputHandler::InputHandler() {
    strategies_ = FcsStrategyFactory::createAll();

    //Set up input
    try {
        inputDevices_.push_back(std::make_unique<Joystick>());
    } catch (const std::runtime_error &e) {
        std::cout << "Did not find a joystick\n";
    }
}

int InputHandler::handleInput(JSBSim::FGFDMExec &fdm) {
    //Keyboard via ncurses. Should be changed.
    /*int ch;
    while ((ch = getch()) != ERR) {
        if (ch == 27) {
            return 0;
        }

        auto res = keyToCommand_.find(ch);
        if (res != keyToCommand_.end()) {
            auto command = commandHandler_.find(res->second);
            if (command != commandHandler_.end()) {
                FcsBinding &binding = command->second;
                strategies_[binding.strategyKey]->adjustValue(fdm, binding.delta);
            }
        }
    }*/

    for (std::unique_ptr<InputDevice> &device: inputDevices_) {
        //This only works with joystick atm
        //Currently, solely SDL manages input
        ControlEvent event;
        device->sampleState(event);

        strategies_["roll"]->setValue(fdm, event.roll);
        strategies_["pitch"]->setValue(fdm, event.pitch);
        strategies_["yaw"]->setValue(fdm, event.yaw);
        strategies_["throttle"]->setValue(fdm, event.slider);
    }

    return 1;
}

/**
 * Handles joystick input.
 * Built to be input framework-agnostic.
 * These currently only handle FCS. Need to expand to work with other bindings.
 * @param fdm The FDM instance.
 */
//void InputHandler::handleJoystick(JSBSim::FGFDMExec &fdm) {

//}
