//
// Created by jay on 6/26/26.
//

#include <fstream>
#include <iostream>
#include <unistd.h>
#include <JSBSim/FGFDMExec.h>
#include <JSBSim/initialization/FGInitialCondition.h>
#include <ncurses.h> //Currently used to print but ideally shouldn't be here
#include <bits/this_thread_sleep.h>
#include "Simulation.h"


/**
 * Constructs the simulator.
 */
Simulation::Simulation() : aircraft_(fdm_) {
    static const char *JSBGITDIR = std::getenv("JSBGITDIR");

    fdm_.SetDebugLevel(0);

    //Set up JSB directories and load models
    const SGPath root(JSBGITDIR);
    fdm_.SetRootDir(root);

    fdm_.SetAircraftPath(SGPath("aircraft"));
    fdm_.SetEnginePath(SGPath("engine"));
    fdm_.SetSystemsPath(SGPath("systems"));

    if (!fdm_.LoadModel("c172p")) {
        throw std::runtime_error("Failed to load aircraft model");
    }

    auto IC = fdm_.GetIC();
    if (!IC->Load(SGPath("reset00.xml"))) {
        throw std::runtime_error("Failed to load reset file");
    }

    //Dump catalog for selected plane
    dumpPropertyCatalogToFile(fdm_, "catalog.txt");

    initscr();
    noecho();
    cbreak();
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);
}

/**
 * Runs the simulation.
 */
void Simulation::run() {
    fdm_.RunIC();
    fdm_.Setdt(0.01);
    double dt = fdm_.GetDeltaT();

    while (true) {
        if (!inputHandler_.handleInput(fdm_)) {
            break;
        }

        fdm_.Run();
        //aircraft_.resetFCS(); //gamified controls reset each tick. This is useful for arcade keyboard input


        //Sleep for sim duration (~8.3ms) to (approximately) match real lifetime.
        //This will inevitably lag the sim
        //Needs to be replaced with some exterior time tracking given that real-time simulation is desired
        std::this_thread::sleep_for(std::chrono::duration<double>(dt));
    }

    endwin();

    std::cout << "Exited successfully" << std::endl;
}

/**
 * @brief Dumps all the adjustable and telemetry properties of the currently used aircraft into a file.
 * @param fdm The FGFDMExec instance
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
