//
// Created by jay on 6/26/26.
//

#include <fstream>
#include <iostream>
#include <JSBSim/FGFDMExec.h>
#include <JSBSim/initialization/FGInitialCondition.h>
#include "Simulation.h"

/**
 * Constructs the simulator.
 */
Simulation::Simulation(const char *aircraftModel, const char *resetFile) : aircraft_(fdm_),
                                                                           inputHandler_(fdm_) {
    if (!std::getenv("JSBGITDIR")) {
        throw std::runtime_error("JSBGITDIR environment variable is not set");
    }
    const char *JSBGITDIR = std::getenv("JSBGITDIR");

    fdm_.SetDebugLevel(0);

    //Set up JSB directories and load models
    const SGPath root(JSBGITDIR);
    fdm_.SetRootDir(root);

    fdm_.SetAircraftPath(SGPath("aircraft"));
    fdm_.SetEnginePath(SGPath("engine"));
    fdm_.SetSystemsPath(SGPath("systems"));

    if (!fdm_.LoadModel(aircraftModel)) {
        throw std::runtime_error("Failed to load aircraft model");
    }

    auto IC = fdm_.GetIC();
    if (!IC->Load(SGPath(resetFile))) {
        throw std::runtime_error("Failed to load reset file");
    }

    //Dump catalog for selected plane
    dumpPropertyCatalogToFile(fdm_, "catalog.txt");

    fdm_.RunIC();
    fdm_.Setdt(0.02);
}

/**
 * Runs a step in the simulation.
 * @param input The data coming from input devices such as joystick, keyboard.
 * @return Sim state to be rendered.
 */
RendererPayload Simulation::run(const std::vector<OutCommand> &input) {
    inputHandler_.handleInput(input);
    aircraft_.updateValues();

    //Update this to contain a proper payload
    RendererPayload p;
    double time = fdm_.GetSimTime();
    p.time = time;
    aircraft_.appendDataTo(p);

    fdm_.Run();

    //aircraft_.resetFCS(); //gamified controls reset each tick. This is useful for arcade keyboard input

    return p;
}

/**
 * @brief Dumps all the adjustable and telemetry properties of the currently used aircraft into a file.
 * @param fdm The simulator instance
 * @param filename The output file name.
 */
void Simulation::dumpPropertyCatalogToFile(JSBSim::FGFDMExec &fdm, const std::string &filename) {
    std::ofstream out(filename);

    if (!out.is_open()) {
        throw std::runtime_error("Failed to open output file");
    }

    std::streambuf *oldBuf = std::cout.rdbuf();
    std::cout.rdbuf(out.rdbuf());

    fdm.PrintPropertyCatalog();

    std::cout.rdbuf(oldBuf);
}
