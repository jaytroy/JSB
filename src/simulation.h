//
// Created by jay on 6/26/26.
//

#ifndef JSB_SIMULATION_H
#define JSB_SIMULATION_H
#include "util/ncursesmanager.h"


class Simulation {
public:
    explicit Simulation();

    void setup();
    void run();

private:
    NCursesManager nCursesManager;
    JSBSim::FGFDMExec fdm;

    static void dumpPropertyCatalogToFile(JSBSim::FGFDMExec &fdm, const std::string &filename);
};


#endif //JSB_SIMULATION_H
