//
// Created by jay on 6/26/26.
//

#ifndef JSB_SIMULATION_H
#define JSB_SIMULATION_H
#include <unordered_map>
#include <JSBSim/FGFDMExec.h>

#include "model/aircraft.h"
#include "util/nCursesManager.h"


class Simulation {
public:
    explicit Simulation();

    void setup();
    void run();

private:
    NCursesManager nCursesManager_;
    JSBSim::FGFDMExec fdm_;
    Aircraft aircraft_;
    std::unordered_map<std::string, std::unique_ptr<FcsStrategy>> strategies_;

    static void dumpPropertyCatalogToFile(JSBSim::FGFDMExec &fdm, const std::string &filename);
};


#endif //JSB_SIMULATION_H
