//
// Created by jay on 6/26/26.
//

#ifndef JSB_AIRCRAFT_H
#define JSB_AIRCRAFT_H
#include <FGFDMExec.h>

#include "fcs/fcsStrategy.h"

/**
 * @brief The aircraft class. Holds and refers to all info about the specific aircraft.
 */
class Aircraft {
public:
    explicit Aircraft(const JSBSim::FGFDMExec &fdm);

    void startAircraft();
    void stopAircraft();

    void adjustFCS(std::unique_ptr<FcsStrategy> &&strategy, double value);

    void setThrottle(double value);
    void setPitch(double value);
    void setRoll(double value);
    void setYaw(double value);
    void resetFCS();

private:
    JSBSim::FGFDMExec fdm;
    int engineOn = 0;
    double throttle = 0.0;
    double rudder = 0.0;
    double elevator = 0.0;
    double aileron = 0.0;
    std::unique_ptr<FcsStrategy> fcsStrategy_;
};


#endif //JSB_AIRCRAFT_H
