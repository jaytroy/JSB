//
// Created by jay on 7/7/26.
//

#include "InputHandler.h"

#include <FGFDMExec.h>
#include <iostream>

#include "AxisDevice.h"
#include "../../input/Joystick.h"
#include "../fcs/FcsStrategyFactory.h"

InputHandler::InputHandler(JSBSim::FGFDMExec &fdm) : fdm_(fdm) {
    strategies_ = FcsStrategyFactory::createAll();

    //Set up input
    try {
        axisDevices_.push_back(std::make_unique<Joystick>());
    } catch ([[maybe_unused]] const std::runtime_error &e) {
        std::cout << "Did not find a joystick\n";
    }
}

int InputHandler::handleInput(JSBSim::FGFDMExec &fdm, const std::vector<int> &input) {
    for (std::unique_ptr<AxisDevice> &device: axisDevices_) {
        //This only works with joystick atm. Needs a refactor
        ControlEvent event{};
        device->sampleState(event);

        strategies_["roll"]->setValue(fdm, event.roll);
        strategies_["pitch"]->setValue(fdm, event.pitch);
        strategies_["yaw"]->setValue(fdm, event.yaw);
        strategies_["throttle"]->setValue(fdm, event.slider);
    }

    std::vector<FcsCommand> cmds;
    for (int i: input) {
        auto cmd = keyToCommand_.find(i);
        if (cmd != keyToCommand_.end()) {
            auto b = commandHandler_.find(cmd->second);
            if (b != commandHandler_.end()) {
                FcsBinding &binding = b->second;
                strategies_[binding.strategyKey]->adjustValue(fdm, binding.delta);
            }
        }
    }

    return 1;
}
