//
// Created by jay on 6/26/26.
//

#ifndef JSB_SIMULATION_H
#define JSB_SIMULATION_H
#include <functional>
#include <unordered_map>
#include <JSBSim/FGFDMExec.h>

#include "model/Aircraft.h"
#include "model/fcs/FcsCommand.h"
#include "util/NCursesManager.h"


class Simulation {
public:
    Simulation();

    void setup();

    void run();

private:
    NCursesManager nCursesManager_;
    JSBSim::FGFDMExec fdm_;
    Aircraft aircraft_;
    std::unordered_map<std::string, std::unique_ptr<FcsStrategy>> uuustrategies_;
    std::unique_ptr<InputDevice> inputDevice_;
    std::unordered_map<FcsCommand, std::function<void()>> commandHandler_;

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
    };

    static void dumpPropertyCatalogToFile(JSBSim::FGFDMExec &fdm, const std::string &filename);
};


#endif //JSB_SIMULATION_H
