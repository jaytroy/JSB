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
#include "input/NCursesManager.h"

/**
 * The simulation class is responsible for running all parts of the simulator and putting them together.
 * This is where we have the main game loop.
 */
class Simulation {
public:
    Simulation();
    void run();

private:
    NCursesManager nCursesManager_;
    JSBSim::FGFDMExec fdm_;
    Aircraft aircraft_;
    std::unique_ptr<InputDevice> inputDevice_;
    std::unordered_map<std::string, std::unique_ptr<FcsStrategy>> strategies_;

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
    };

    /**
     * Dumps the entirety property catalog of the current aircraft into a file.
     * This is primarily for ease of development.
     * @brief Lets you look up things like "fcs/throttle..."
     * @param fdm The fdm instance.
     * @param filename The output filename.
     */
    static void dumpPropertyCatalogToFile(JSBSim::FGFDMExec &fdm, const std::string &filename);
};


#endif //JSB_SIMULATION_H
