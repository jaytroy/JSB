//
// Created by jay on 7/7/26.
//

#include "InputHandler.h"

#include <FGFDMExec.h>
#include <utility>

#include "../../data/AxisDevice.hpp"
#include "../fcs/FcsStrategyFactory.hpp"


InputHandler::InputHandler(JSBSim::FGFDMExec &fdm) : fdm_(fdm) {
    strategies_ = FcsStrategyFactory::createAll();

}

int InputHandler::handleInput(JSBSim::FGFDMExec &fdm, const std::vector<int> &input) {
    for (auto& [index, device]: axisDevices_) {
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
