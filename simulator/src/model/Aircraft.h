//
// Created by jay on 6/26/26.
//

#ifndef JSB_AIRCRAFT_H
#define JSB_AIRCRAFT_H
#include <FGFDMExec.h>

/**
 * @brief The aircraft class. Holds all info about the specific aircraft.
 */
class Aircraft {
public:
    explicit Aircraft(JSBSim::FGFDMExec &fdm);

    void resetFCS();
    void updateValues();
    void appendData(std::vector<double>& rendererPayload);

private:
    JSBSim::FGFDMExec &fdm_;

    int engineOn = 0;
    double throttle = 0.0;
    double rudder = 0.0;
    double elevator = 0.0;
    double aileron = 0.0;
    double airspeed = 0.0;
    double posN = 0.0;
    double posE = 0.0;
    double posU = 0.0;
    double rpm = 0.0;
    double heading = 0.0;
    double brake = 0.0;
    double roll = 0.0;
    double pitch = 0.0;
};


#endif //JSB_AIRCRAFT_H
