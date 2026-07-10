#include "Simulation.h"

constexpr std::string AIRCRAFT_MODEL = "c172p";

/**
 * Welcome to this minimal JSB simulator. It's quite barebones right now, but it will keep getting bigger ;)
 * @return
 */
int main() {
    Simulation sim(AIRCRAFT_MODEL);
    sim.run();
}
