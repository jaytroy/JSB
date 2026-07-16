//
// Created by jay on 7/7/26.
//

#ifndef JSB_INPUTHANDLER_H
#define JSB_INPUTHANDLER_H

#include <FGFDMExec.h>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#include "../../shared/AxisDevice.hpp"
#include "../../shared/FcsCommand.h"
#include "../../shared/FcsTarget.h"
#include "../fcs/FcsStrategy.h"


class InputHandler {
public:
    explicit InputHandler(JSBSim::FGFDMExec &fdm);

    /**
     * Handles (applies) the input given to the simulation.
     * @param fdm The sim instance.
     * @param input A vector of commands to be processed this tick.
     * @return The success of the handling.
     */
    int handleInput(JSBSim::FGFDMExec& fdm, std::vector<OutCommand>& input);

private:
    JSBSim::FGFDMExec& fdm_;
    std::unordered_map<FcsTarget, std::unique_ptr<FcsStrategy> > strategies_;

    std::unordered_map<FcsCommand, double> commandHandler_ = {
        {FcsCommand::PitchUp, -1.0},
        {FcsCommand::PitchDown, 1.0},
        {FcsCommand::RollLeft, -1.0},
        {FcsCommand::RollRight, 1.0},
        {FcsCommand::YawLeft, 1.0},
        {FcsCommand::YawRight, -1.0},
        {FcsCommand::ThrottleUp, 0.1},
        {FcsCommand::ThrottleDown, -0.1},
        {FcsCommand::ToggleBrake, 0.01},
        {FcsCommand::ToggleEngine, 0.0}
    };
};

#endif //JSB_INPUTHANDLER_H
