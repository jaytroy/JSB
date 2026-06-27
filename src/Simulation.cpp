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

#include "model/fcs/actions/Pitch.h"
#include "model/fcs/actions/Roll.h"
#include "model/fcs/actions/Throttle.h"
#include "model/fcs/actions/Yaw.h"


Simulation::Simulation() {
}

void Simulation::setup() {
    //Set up JSB
    JSBSim::FGFDMExec fdm;

    SGPath root("/home/jay/Proj/jsbsim");
    fdm.SetRootDir(root);

    fdm.SetAircraftPath(SGPath("/aircraft"));
    fdm.SetEnginePath(SGPath("/engine"));
    fdm.SetSystemsPath(SGPath("/systems"));

    if (!fdm.LoadModel("c172p")) {
        throw std::runtime_error("Failed to load aircraft model");
    }

    auto IC = fdm.GetIC();
    if (!IC->Load(SGPath("/home/jay/Proj/jsbsim/aircraft/c172p/reset00.xml"))) {
        throw std::runtime_error("Failed to load reset file");
    }

    dumpPropertyCatalogToFile(fdm, "catalog.txt");

    //Set up FCS strategies
    //This can be made better with a factory
    strategies_["throttle"] = std::make_unique<Throttle>();
    strategies_["pitch"] = std::make_unique<Pitch>();
    strategies_["yaw"] = std::make_unique<Yaw>();
    strategies_["roll"] = std::make_unique<Roll>();

    commandHandler_ = {
        {FcsCommand::PitchUp,   [this]() { strategies_["pitch"]->adjustValue(fdm_, 0.1); }},
        {FcsCommand::PitchDown, [this]() { strategies_["pitch"]->adjustValue(fdm_, -0.1); }},
        {FcsCommand::RollLeft,  [this]() { strategies_["roll"]->adjustValue(fdm_, -0.1); }},
        {FcsCommand::RollRight, [this]() { strategies_["roll"]->adjustValue(fdm_, 0.1); }},
        {FcsCommand::YawLeft, [this]() { strategies_["yaw"]->adjustValue(fdm_, 0.1); }},
        {FcsCommand::YawRight, [this]() { strategies_["yaw"]->adjustValue(fdm_, 0.1); }},
    };
}

void Simulation::run() {

    double dt = fdm_.GetDeltaT();

    fdm_.RunIC();
    fdm_.Setdt(0.01);
    while (true) {
        int c = CursesManager_.getInput();


        InputEvent event;
        while (inputDevice_->pollEvent(event)) {
            auto res = keyBindings_.find(event.code);
            if (res !=keyBindings_.end()) {
                res->second();
            }
        }
        //Need to move this out
        if (c == 27)
            break;

        if (c == KEY_UP)
            strategies_.adjustFCS(Pitch, 0.1);
        if (c == KEY_DOWN)
            throttle -= 0.01;
        //Clamp throttle
        if (throttle > 1.0) throttle = 1.0;
        if (throttle < 0.0) throttle = 0.0;

        

        if (c == KEY_BACKSPACE) {
            if (fdm_.GetPropertyValue("fcs/left-brake-cmd-norm") == 0.0) {

            } else {
                fdm_.SetPropertyValue("fcs/left-brake-cmd-norm", 0.0);
                fdm_.SetPropertyValue("fcs/right-brake-cmd-norm", 0.0);
                fdm_.SetPropertyValue("fcs/center-brake-cmd-norm", 0.0);
            }
        }

        //Control surfaces
        if (c == 's') {
            elevator = 1.0;
        } else if (c == 'w') {
            elevator = -1.0;
        }
        if (c == 'd') {
            aileron = 1.0;
        } else if (c == 'a') {
            aileron = -1.0;
        }
        if (c == 'q') {
            rudder = -1.0;
        } else if (c == 'e') {
            rudder = 1.0;
        }

        //up to here

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

        //Sleep for sim duration (~8.3ms) to match real life time.
        //This will likely lag the sim if dense enough
        std::this_thread::sleep_for(std::chrono::duration<double>(dt));
    }

    endwin();

    std::cout << "Exited" << std::endl;
}


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

