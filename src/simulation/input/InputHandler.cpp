//
// Created by jay on 7/7/26.
//

#include "InputHandler.h"

#include <FGFDMExec.h>
#include <utility>

#include "../fcs/FcsStrategyFactory.hpp"


InputHandler::InputHandler(JSBSim::FGFDMExec &fdm) : fdm_(fdm) {
    strategies_ = FcsStrategyFactory::createAll();

}

int InputHandler::handleInput(JSBSim::FGFDMExec &fdm, const std::vector<int> &inputD, const std::vector<OutCommand>& inputA) {
    //Need to merge these two loops
    for (auto input: inputA) {
        strategies_[targetOf(input.first)]->setValue(fdm, input.second);
    }

    std::vector<FcsCommand> cmds;
    for (int i: inputD) {
        auto cmd = keyToCommand_.find(i);
        if (cmd != keyToCommand_.end()) {

            strategies_[targetOf(cmd->second)]->adjustValue(fdm, commandHandler_.find(cmd->second)->second);
        }
    }

    return 1;
}
