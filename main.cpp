#include <fstream>
#include <iostream>
#include <unistd.h>
#include <JSBSim/FGFDMExec.h>
#include <JSBSim/models/FGAircraft.h>
#include <JSBSim/initialization/FGInitialCondition.h>
#include <ncurses.h>
#include <bits/this_thread_sleep.h>

void DumpPropertyCatalogToFile(JSBSim::FGFDMExec &fdm, const std::string &filename) {
    std::ofstream out(filename);

    if (!out.is_open()) {
        throw std::runtime_error("Failed to open output file");
    }

    std::streambuf *oldBuf = std::cout.rdbuf();
    std::cout.rdbuf(out.rdbuf());

    fdm.PrintPropertyCatalog();

    std::cout.rdbuf(oldBuf);
}

int main() {
    //Ncurses setup
    initscr();
    noecho();
    cbreak();
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);

    //JSB setup
    JSBSim::FGFDMExec fdm;

    SGPath root(".");
    fdm.SetRootDir(root);

    fdm.SetAircraftPath(SGPath("/home/jay/Proj/jsbsim/aircraft"));
    fdm.SetEnginePath(SGPath("/home/jay/Proj/jsbsim/engine"));
    fdm.SetSystemsPath(SGPath("/home/jay/Proj/jsbsim/systems"));

    if (!fdm.LoadModel("c172p")) {
        std::cerr << "Failed to load aircraft model\n";
        return 1;
    }

    auto IC = fdm.GetIC();
    if (!IC->Load(SGPath("/home/jay/Proj/jsbsim/aircraft/c172p/reset00.xml"))) {
        std::cerr << "Failed to load IC file\n";
        return 1;
    }

    fdm.RunIC();
    fdm.Setdt(0.01);

    //Setup ends here

    DumpPropertyCatalogToFile(fdm, "catalog.txt");

    //This is the sim loop
    double throttle = 0.0;
    double rudder = 0.0;
    double elevator = 0.0;
    double aileron = 0.0;

    fdm.SetPropertyValue("fcs/elevator-trim-cmd-norm", 0.2);

    int engineOn = 0;

    double dt = fdm.GetDeltaT();

    while (true) {
        int c = getch();

        if (c == 27)
            break;

        if (c == 'p' && !engineOn) {
            fdm.SetPropertyValue("propulsion/engine/set-running", 1);
            fdm.SetPropertyValue("propulsion/starter_cmd", 1);
            fdm.SetPropertyValue("fcs/mixture-cmd-norm", 1.0);
            fdm.SetPropertyValue("propulsion/magneto_cmd", 3);
            engineOn = 1;
        } else if (c == 'p' && engineOn) {
            fdm.SetPropertyValue("propulsion/engine/set-running", 0);
            fdm.SetPropertyValue("propulsion/starter_cmd", 0);
            fdm.SetPropertyValue("fcs/mixture-cmd-norm", 0.0);
            fdm.SetPropertyValue("propulsion/magneto_cmd", 0);
            engineOn = 0;
        }

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
        } else if(c == 'e') {
            rudder = 1.0;
        }

        fdm.SetPropertyValue("fcs/throttle-cmd-norm", throttle);
        fdm.SetPropertyValue("fcs/rudder-cmd-norm", rudder);
        fdm.SetPropertyValue("fcs/aileron-cmd-norm", aileron);
        fdm.SetPropertyValue("fcs/elevetor-cmd-norm", elevator);

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
            time,airspeed,throttle,rpm,posN,posE,posU,heading,rudder,brake,roll);

        refresh();

        //Reset fcs
        rudder = 0.0;
        elevator = 0.0;
        aileron = 0.0;

        std::this_thread::sleep_for(std::chrono::duration<double>(dt));
    }
    endwin();

    std::cout << "Exited" << std::endl;

    return 0;
}
