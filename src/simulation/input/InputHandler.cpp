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

int InputHandler::handleInput(JSBSim::FGFDMExec &fdm, const std::vector<OutCommand>& input) {
    //Need to merge these two loops
    for (auto out: input) {
        //strategies_[targetOf(out.first)]->setValue(fdm, out.second);
        strategies_[targetOf(out.first)]->adjustValue(fdm, commandHandler_.find(out.first)->second);
    }

    /*
    std::vector<FcsCommand> cmds;
    for (int i: inputD) {
        auto cmd = keyToCommand_.find(i);
        if (cmd != keyToCommand_.end()) {

            strategies_[targetOf(cmd->second)]->adjustValue(fdm, commandHandler_.find(cmd->second)->second);
        }
    }
*/
    return 1;
}
