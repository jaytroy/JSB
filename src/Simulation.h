//
// Created by jay on 6/26/26.
//

#ifndef JSB_SIMULATION_H
#define JSB_SIMULATION_H
#include <functional>
#include <unordered_map>
#include <JSBSim/FGFDMExec.h>

#include "gfx/Window.h"
#include "model/input/InputDevice.h"
#include "model/Aircraft.h"
#include "model/fcs/FcsCommand.h"
#include "model/input/InputHandler.h"

/**
 * The simulation class is responsible for running all parts of the simulator and putting them together.
 * This is where we have the main game loop.
 */
class Simulation {
public:
    Simulation();
    void run();

private:
    JSBSim::FGFDMExec fdm_;
    Aircraft aircraft_;
    InputHandler inputHandler_;
    Window window_;

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
