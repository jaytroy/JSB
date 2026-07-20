//
// Created by jay on 6/26/26.
//

#ifndef JSB_SIMULATION_H
#define JSB_SIMULATION_H
#include <JSBSim/FGFDMExec.h>

#include <utility>

#include "Aircraft.h"
#include "input/InputHandler.h"

/**
 * The simulation class is responsible for running all parts of the simulator and putting them together.
 * This is where we have the main game loop.
 */
class Simulation {
public:
    Simulation(const char *aircraftModel, const char *resetFile);

    RendererPayload run(const std::vector<OutCommand> &input);
    double getDt() const { return fdm_.GetDeltaT(); }

private:
    JSBSim::FGFDMExec fdm_;
    Aircraft aircraft_;
    InputHandler inputHandler_;

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
