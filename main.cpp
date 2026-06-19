#include <fstream>
#include <iostream>
#include <unistd.h>
#include <JSBSim/FGFDMExec.h>
#include <ncurses.h>

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

    fdm.LoadModel("c172p");

    fdm.RunIC();
    fdm.Setdt(0.01);

    //Setup ends here

    DumpPropertyCatalogToFile(fdm, "catalog.txt");

    //This is the sim loop
    double throttle = 0.0;



    fdm.SetPropertyValue("fcs/elevator-trim-cmd-norm", 0.2);

    while (true) {
        int c = getch();

        if (c == 27)
            break;

        double time = fdm.GetSimTime();
        double airspeed = fdm.GetPropertyValue("velocities/vc-kts");

        if (c == 's') {
            fdm.SetPropertyValue("propulsion/engine/set-running", 1);
            fdm.SetPropertyValue("propulsion/starter_cmd", 1);
            fdm.SetPropertyValue("fcs/mixture-cmd-norm", 1.0);
        }
        if (c == KEY_UP)
            throttle += 0.01;
        if (c == KEY_DOWN)
            throttle -= 0.01;
        if (c == KEY_BACKSPACE) {
            fdm.SetPropertyValue("fcs/left-brake-cmd-norm", 1.0);
            fdm.SetPropertyValue("fcs/right-brake-cmd-norm", 1.0);
            fdm.SetPropertyValue("fcs/center-brake-cmd-norm", 1.0);
        }


        fdm.SetPropertyValue("fcs/throttle-cmd-norm", throttle);

        fdm.Run();

        erase();
        printw("t=%f\nv=%f\nthrottle=%f\nrpm=%f\nposit_x=%lf\nposit_y=%lf\n",
        time, airspeed, throttle, fdm.GetPropertyValue("propulsion/engine/engine-rpm")), fdm.GetPropertyValue("position/distance-from-start-lon-mt"), fdm.GetPropertyValue("position/distance-from-start-lat-mt");
        refresh();
    }

    endwin();

    std::cout << "Exited" << std::endl;
    return 0;
}
