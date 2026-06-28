//
// Created by jay on 6/26/26.
//

#ifndef JSB_AIRCRAFT_H
#define JSB_AIRCRAFT_H
#include <FGFDMExec.h>

#include "fcs/FcsStrategy.h"

/**
 * @brief The aircraft class. Holds all info about the specific aircraft and enables interaction with it.
 */
class Aircraft {
public:
    explicit Aircraft(JSBSim::FGFDMExec &fdm);

    void startAircraft();
    void stopAircraft();
    void resetFCS();

private:
    JSBSim::FGFDMExec &fdm_;
    int engineOn = 0;
    double throttle = 0.0;
    double rudder = 0.0;
    double elevator = 0.0;
    double aileron = 0.0;
    std::unique_ptr<FcsStrategy> fcsStrategy_;
};


#endif //JSB_AIRCRAFT_H
