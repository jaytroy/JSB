#include "SimRunner.hpp"

#define AIRCRAFT_MODEL "c172p"
#define RESET_FILE "reset00.xml"

/**
 * Welcome to this minimal JSB simulator. It's quite barebones right now, but it will keep getting bigger ;)
 * @return
 */
int main() {
    SimRunner simRunner(AIRCRAFT_MODEL, RESET_FILE);
    simRunner.run();

    return 0;
}