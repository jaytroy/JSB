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

#include "InputDevice.h"
#include "../fcs/FcsCommand.h"
#include "../fcs/FcsStrategy.h"


class InputHandler {
public:
    InputHandler();
    int handleInput(JSBSim::FGFDMExec &fdm); //I don't rly want the fdm instance here but I think it's necesary

private:

    std::unordered_map<std::string, std::unique_ptr<FcsStrategy>> strategies_;
    std::vector<std::unique_ptr<InputDevice>> inputDevices_;

    //This translation should happen here
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

    //I still don't like this
    //I can go directly key to command, but is that better?
    std::unordered_map<FcsCommand, FcsBinding> commandHandler_ = {
        {FcsCommand::PitchUp, {"pitch", 0.1}},
        {FcsCommand::PitchDown, {"pitch", -0.1}},
        {FcsCommand::RollLeft, {"roll", -0.1}},
        {FcsCommand::RollRight, {"roll", 0.1}},
        {FcsCommand::YawLeft, {"yaw", -0.1}},
        {FcsCommand::YawRight, {"yaw", 0.1}},
        {FcsCommand::ThrottleUp, {"throttle", 0.1}},
        {FcsCommand::ThrottleDown, {"throttle", -0.1}},
        {FcsCommand::ToggleBrake, {"brake", 0.0}},
        {FcsCommand::ToggleEngine, {"engine", 0.0}}
    };
};


#endif //JSB_INPUTHANDLER_H
