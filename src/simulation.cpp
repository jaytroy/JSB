//
// Created by jay on 6/26/26.
//

#include <fstream>
#include <iostream>
#include <unistd.h>
#include <JSBSim/FGFDMExec.h>
#include <JSBSim/models/FGAircraft.h>
#include <JSBSim/initialization/FGInitialCondition.h>
#include <ncurses.h>
#include <bits/this_thread_sleep.h>
#include "simulation.h"


Simulation::Simulation()
    : fdm(), nCursesManager()
{}

void Simulation::setup() {
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
}

void Simulation::run() {

    double dt = fdm.GetDeltaT();

    fdm.RunIC();
    fdm.Setdt(0.01);
    while (true) {
        int c = nCursesManager.input();

        //Need to move this out
        if (c == 27)
            break;

        if (c == KEY_UP)
            throttle += 0.01;
        if (c == KEY_DOWN)
            throttle -= 0.01;
        //Clamp throttle
        if (throttle > 1.0) throttle = 1.0;
        if (throttle < 0.0) throttle = 0.0;

        

        if (c == KEY_BACKSPACE) {
            if (fdm.GetPropertyValue("fcs/left-brake-cmd-norm") == 0.0) {
                fdm.SetPropertyValue("fcs/left-brake-cmd-norm", 1.0);
                fdm.SetPropertyValue("fcs/right-brake-cmd-norm", 1.0);
                fdm.SetPropertyValue("fcs/center-brake-cmd-norm", 1.0);
            } else {
                fdm.SetPropertyValue("fcs/left-brake-cmd-norm", 0.0);
                fdm.SetPropertyValue("fcs/right-brake-cmd-norm", 0.0);
                fdm.SetPropertyValue("fcs/center-brake-cmd-norm", 0.0);
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

        fdm.Run();

        erase();

        double time = fdm.GetSimTime();
        double airspeed = fdm.GetPropertyValue("velocities/vc-kts");
        double posN = fdm.GetPropertyValue("position/from-start-neu-n-ft");
        double posE = fdm.GetPropertyValue("position/from-start-neu-e-ft");
        double posU = fdm.GetPropertyValue("position/from-start-neu-u-ft");
        double rpm = fdm.GetPropertyValue("propulsion/engine/engine-rpm");
        double heading = fdm.GetPropertyValue("attitude/heading-true-rad") * (180.0 / 3.141592653589793238463);
        double brake = fdm.GetPropertyValue("fcs/center-brake-cmd-norm");
        double roll = fdm.GetPropertyValue("attitude/roll-rad");
        double throttle = fdm.GetPropertyValue("propulsion/throttle-pos-norm");
        double rudder = fdm.GetPropertyValue("fcs/rudder-prop-norm");
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

