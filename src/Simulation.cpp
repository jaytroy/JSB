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

#include "model/fcs/actions/Brake.h"
#include "model/fcs/actions/Pitch.h"
#include "model/fcs/actions/Roll.h"
#include "model/fcs/actions/Throttle.h"
#include "model/fcs/actions/Yaw.h"


Simulation::Simulation() : aircraft_(fdm_) {
    //Redirect JSB output
    //std::ofstream logFile("jsbsim.log");
    //std::cout.rdbuf(logFile.rdbuf());
    //std::cerr.rdbuf(logFile.rdbuf());

    //SGPath root("/home/jay/Proj/jsbsim");
    SGPath root(".");
    fdm_.SetRootDir(root);

    fdm_.SetAircraftPath(SGPath("/home/jay/Proj/jsbsim/aircraft"));
    fdm_.SetEnginePath(SGPath("/home/jay/Proj/jsbsim/engine"));
    fdm_.SetSystemsPath(SGPath("/home/jay/Proj/jsbsim/systems"));

    if (!fdm_.LoadModel("c172p")) {
        throw std::runtime_error("Failed to load aircraft model");
    }

    auto IC = fdm_.GetIC();
    if (!IC->Load(SGPath("/home/jay/Proj/jsbsim/aircraft/c172p/reset00.xml"))) {
        throw std::runtime_error("Failed to load reset file");
    }

    //Dump catalog
    dumpPropertyCatalogToFile(fdm_, "catalog.txt");

    //Set up input
    inputDevice_ = std::make_unique<NCursesManager>();

    //Set up FCS strategies
    //This can likely be moved out
    //This can be made better with a factory
    strategies_["throttle"] = std::make_unique<Throttle>();
    strategies_["pitch"] = std::make_unique<Pitch>();
    strategies_["yaw"] = std::make_unique<Yaw>();
    strategies_["roll"] = std::make_unique<Roll>();
    strategies_["brake"] = std::make_unique<Brake>();

    commandHandler_ = {
        {FcsCommand::PitchUp, [this]() { strategies_["pitch"]->adjustValue(fdm_, 0.1); }},
        {FcsCommand::PitchDown, [this]() { strategies_["pitch"]->adjustValue(fdm_, -0.1); }},
        {FcsCommand::RollLeft, [this]() { strategies_["roll"]->adjustValue(fdm_, -0.1); }},
        {FcsCommand::RollRight, [this]() { strategies_["roll"]->adjustValue(fdm_, 0.1); }},
        {FcsCommand::YawLeft, [this]() { strategies_["yaw"]->adjustValue(fdm_, 0.1); }},
        {FcsCommand::YawRight, [this]() { strategies_["yaw"]->adjustValue(fdm_, 0.1); }},
        {FcsCommand::ThrottleUp, [this]() { strategies_["throttle"]->adjustValue(fdm_, 0.01); }},
        {FcsCommand::ThrottleDown, [this]() { strategies_["throttle"]->adjustValue(fdm_, 0.01); }},
        {FcsCommand::ToggleBrake, [this]() {strategies_["brake"]->adjustValue(fdm_, 0.0); }}
    };
}


void Simulation::run() {
    double dt = fdm_.GetDeltaT();

    aircraft_.startAircraft();

    fdm_.RunIC();
    fdm_.Setdt(0.01);
    while (true) {
        //Currently missing shutdown logic (SIGINT termination only)

        InputEvent event;
        while (inputDevice_->pollEvent(event)) {
            printf("Pressed %c\n", event.code);
            if (event.code == 27) {
                //Escape key pressed
                goto simEnd;
            }

            auto res = keyToCommand_.find(event.code);
            if (res != keyToCommand_.end()) {
                auto command = commandHandler_.find(res->second);
                if (command != commandHandler_.end()) {
                    command->second();
                    printf("here\n");
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
        double roll = fdm_.GetPropertyValue("attitude/roll-rad");
        double throttle = fdm_.GetPropertyValue("propulsion/throttle-pos-norm");
        double rudder = fdm_.GetPropertyValue("fcs/rudder-prop-norm");
        printw(
            "t=%f\n"
            "v=%f\n"
            "throttle=%f\n"
            "rpm=%lf\n"
            "posit_n=%lf\n"
            "posit_e=%lf\n"
            "posit_u=%lf\n"
            "heading=%lf\n"
            "rudder=%lf\n"
            "brake=%lf\n"
            "roll=%lf\n",
            time, airspeed, throttle, rpm, posN, posE, posU, heading, rudder, brake, roll);

        refresh();

        //Sleep for sim duration (~8.3ms) to (approximately) match real lifetime.
        //This will inevitably lag the sim a bit
        //Needs to be replaced with some exterior time tracking given that real-time simulation is desired
        std::this_thread::sleep_for(std::chrono::duration<double>(dt));
    }

    simEnd:

    endwin();

    std::cout << "Exited successfully" << std::endl;
}


/**
 * @brief Dumps all the adjustable and telemetry properties of the currently used aircraft into a file.q
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

