#include "Simulation.h"

constexpr std::string AIRCRAFT_MODEL = "c172p";
constexpr std::string RESET_FILE = "reset00.xml";

//Make sure to set the JSBSIMDIR environnment variable

/**
 * Welcome to this minimal JSB simulator. It's quite barebones right now, but it will keep getting bigger ;)
 * @return
 */
int main() {
    Simulation sim(AIRCRAFT_MODEL, RESET_FILE);
    sim.run();
}
