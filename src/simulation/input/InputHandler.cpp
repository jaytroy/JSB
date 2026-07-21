//
// Created by jay on 7/7/26.
//

#include "InputHandler.h"

#include <FGFDMExec.h>
#include <utility>

#include "../fcs/FcsStrategyFactory.hpp"

InputHandler::InputHandler(JSBSim::FGFDMExec& fdm) : fdm_(fdm) {
    strategies_ = FcsStrategyFactory::createAll();
}

int InputHandler::handleInput(const std::vector<OutCommand>& input) {
    for (auto out: input) {
        switch (out.type) {
            case Continuous: strategies_[FcsTarget::targetOf(out.command)]->setValue(fdm_, out.value); break;
            case Discrete: {
                const auto it = commandHandler_.find(out.command);
                const double delta = it != commandHandler_.end() ? it->second : out.value;
                strategies_[targetOf(out.command)]->adjustValue(fdm_, delta);
                break;
            }
        }
    }
    return 1;
}
