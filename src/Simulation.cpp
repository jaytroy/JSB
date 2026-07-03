//
// Created by jay on 6/26/26.
//

#include <fstream>
#include <iostream>
#include <unistd.h>
#include <JSBSim/FGFDMExec.h>
#include <JSBSim/initialization/FGInitialCondition.h>
#include <ncurses.h>
#include <bits/this_thread_sleep.h>
#include "Simulation.h"

#include "input/Joystick.h"
#include "input/SdlManager.h"
#include "model/fcs/FcsStrategyFactory.h"

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

    //Set up input
    inputDevices_.push_back(std::make_unique<SdlManager>());
    inputDevices_.push_back(std::make_unique<Joystick>());

    //Set up FCS strategies
    strategies_ = FcsStrategyFactory::createAll();

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
        //Should this be here?
        for (std::unique_ptr<InputDevice> &device: inputDevices_) {
            std::vector<InputEvent> events;
            device->pollEvents(events);
            for (InputEvent event: events) {
                if (event.keyCode == 27) {
                    //Escape key pressed
                    goto simEnd;
                }

                //This needs better handling. Testing like this for now.
                if (event.keyCode == -10) {
                    FcsBinding pitch;
                    pitch.strategyKey = "pitch";
                    pitch.delta = event.pitch;
                    FcsBinding yaw;
                    yaw.strategyKey = "yaw";
                    yaw.delta = event.yaw;
                    FcsBinding roll;
                    roll.strategyKey = "roll";
                    roll.delta = event.roll;

                    strategies_[pitch.strategyKey]->adjustValue(fdm_, pitch.delta);
                    strategies_[yaw.strategyKey]->adjustValue(fdm_, yaw.delta);
                    strategies_[roll.strategyKey]->adjustValue(fdm_, roll.delta);
                } else if (event.keyCode >= 0) {
                    auto res = keyToCommand_.find(event.keyCode);
                    if (res != keyToCommand_.end()) {
                        auto command = commandHandler_.find(res->second);
                        if (command != commandHandler_.end()) {
                            auto &binding = command->second;
                            strategies_[binding.strategyKey]->adjustValue(fdm_, binding.delta);
                        }
                    }
                }
            }
        }

        fdm_.Run();

        //Erase previous buffer
        erase();

        double time = fdm_.GetSimTime();
        double airspeed = fdm_.GetPropertyValue("velocities/vc-kts");
        double posN = fdm_.GetPropertyValue("position/from-start-neu-n-ft");
        double posE = fdm_.GetPropertyValue("position/from-start-neu-e-ft");
        double posU = fdm_.GetPropertyValue("position/from-start-neu-u-ft");
        double rpm = fdm_.GetPropertyValue("propulsion/engine/engine-rpm");
        double heading = fdm_.GetPropertyValue("attitude/heading-true-rad") * (180.0 / 3.141592653589793238463);
        double brake = fdm_.GetPropertyValue("fcs/center-brake-cmd-norm");
        double roll = fdm_.GetPropertyValue("fcs/aileron-cmd-norm");
        double throttle = fdm_.GetPropertyValue("fcs/throttle-cmd-norm");
        double pitch = fdm_.GetPropertyValue("fcs/pitch-cmd-norm");
        printw(
            "t=%f\n"
            "v=%f\n"
            "throttle=%f\n"
            "rpm=%lf\n"
            "posit_n=%lf\n"
            "posit_e=%lf\n"
            "posit_u=%lf\n"
            "heading=%lf\n"
            "pitch=%lf\n"
            "roll=%lf\n"
            "brake=%lf\n",
            time, airspeed, throttle, rpm, posN, posE, posU, heading, pitch, roll, brake);

        refresh();

        aircraft_.resetFCS();

        //Sleep for sim duration (~8.3ms) to (approximately) match real lifetime.
        //This will inevitably lag the sim
        //Needs to be replaced with some exterior time tracking given that real-time simulation is desired
        std::this_thread::sleep_for(std::chrono::duration<double>(dt));
    }

simEnd:

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
