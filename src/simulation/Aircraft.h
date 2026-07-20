//
// Created by jay on 6/26/26.
//

#ifndef JSB_AIRCRAFT_H
#define JSB_AIRCRAFT_H
#include <FGFDMExec.h>

#include "shared/RendererPayload.hpp"

/**
 * @brief The aircraft class. Holds all info about the specific aircraft.
 */
class Aircraft {
public:
    explicit Aircraft(JSBSim::FGFDMExec &fdm);

    void resetFCS() const;
    void updateValues();
    void appendDataTo(RendererPayload &rendererPayload) const;

private:
    JSBSim::FGFDMExec &fdm_;

    int engineOn_ = 0;
    double throttle_ = 0.0;
    double rudder_ = 0.0;
    double elevator_ = 0.0;
    double aileron_ = 0.0;
    double airspeed_ = 0.0;
    double posN_ = 0.0;
    double posE_ = 0.0;
    double posU_ = 0.0;
    double rpm_ = 0.0;
    double heading_ = 0.0;
    double brake_ = 0.0;
    double roll_ = 0.0;
    double pitch_ = 0.0;
};


#endif //JSB_AIRCRAFT_H
