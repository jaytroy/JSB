#include "SimRunner.hpp"

#define AIRCRAFT_MODEL "c172p"
#define RESET_FILE "reset00.xml"

/**
 * Welcome to this minimal JSB simulator. It's quite barebones right now, but it will keep getting bigger ;)
 * @return
 */
int main(int argc, char** argv) {
    SimRunner simRunner(AIRCRAFT_MODEL, RESET_FILE);
    if (argc != 0) {
        simRunner.updateSim();
    }

    simRunner.run();

    return 0;
}