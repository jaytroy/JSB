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

#include "../../data/AxisDevice.hpp"
#include "../fcs/FcsCommand.h"
#include "../fcs/FcsStrategy.h"


class InputHandler {
public:
    explicit InputHandler(JSBSim::FGFDMExec &fdm);

    InputHandler(JSBSim::FGFDMExec &fdm, std::unordered_map<int, std::unique_ptr<AxisDevice>> devices);

    int handleInput(JSBSim::FGFDMExec &fdm, const std::vector<int> &input); //I don't rly want the fdm instance here but I think it's necesary

    void setInputDevices(std::unordered_map<int, std::unique_ptr<AxisDevice>> devices) { axisDevices_ = std::move(devices); }

private:
    JSBSim::FGFDMExec& fdm_;
    std::unordered_map<std::string, std::unique_ptr<FcsStrategy> > strategies_;
    std::unordered_map<int, std::unique_ptr<AxisDevice>> axisDevices_;

    //These should Ideally be read from config files.
    std::unordered_map<int, FcsCommand> keyToCommand_ = {
        {'w', FcsCommand::PitchDown},
        {'s', FcsCommand::PitchUp},
        {'a', FcsCommand::RollLeft},
        {'d', FcsCommand::RollRight},
        {'q', FcsCommand::YawLeft},
        {'e', FcsCommand::YawRight},
        {'u', FcsCommand::ThrottleUp},
        {'n', FcsCommand::ThrottleDown},
        {'b', FcsCommand::ToggleBrake},
        {'p', FcsCommand::ToggleEngine}
    };
 
    std::unordered_map<FcsCommand, FcsBinding> commandHandler_ = {
        {FcsCommand::PitchUp, {"pitch", -1}},
        {FcsCommand::PitchDown, {"pitch", 1}},
        {FcsCommand::RollLeft, {"roll", -1}},
        {FcsCommand::RollRight, {"roll", 1}},
        {FcsCommand::YawLeft, {"yaw", 1}},
        {FcsCommand::YawRight, {"yaw", -1}},
        {FcsCommand::ThrottleUp, {"throttle", 0.1}},
        {FcsCommand::ThrottleDown, {"throttle", -0.1}},
        {FcsCommand::ToggleBrake, {"brake", 0.01}},
        {FcsCommand::ToggleEngine, {"engine", 0.0}}
    };
};

#endif //JSB_INPUTHANDLER_H
