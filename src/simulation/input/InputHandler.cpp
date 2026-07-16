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

int InputHandler::handleInput(JSBSim::FGFDMExec& fdm, std::vector<OutCommand>& input) {
    for (auto out: input) {
        switch (out.type) {
            case Continuous: strategies_[targetOf(out.command)]->setValue(fdm, out.value); break;
            case Discrete: strategies_[targetOf(out.command)]
                ->adjustValue(fdm, commandHandler_.find(out.command)->second); break;
        }
    }
    return 1;
}
