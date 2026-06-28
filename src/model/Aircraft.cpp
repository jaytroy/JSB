//
// Created by jay on 6/26/26.
//

#include "Aircraft.h"

#include <FGFDMExec.h>
#include <stdexcept>
#include <models/FGPropagate.h>

#include "fcs/FcsStrategy.h"

/**
 * @brief Aircraft::Aircraft constructs a new aircraft to be used in the sim.
 * @return The aircraft.
 */
Aircraft::Aircraft(JSBSim::FGFDMExec &fdm)
    : fdm_(fdm) {}

void Aircraft::startAircraft() {
    fdm_.SetPropertyValue("propulsion/engine/set-running", 1);
    fdm_.SetPropertyValue("propulsion/starter_cmd", 1);
    fdm_.SetPropertyValue("fcs/mixture-cmd-norm", 1.0);
    fdm_.SetPropertyValue("propulsion/magneto_cmd", 3);
    fdm_.SetPropertyValue("fcs/elevator-trim-cmd-norm", 0.2);
    engineOn = 1;
}

void Aircraft::stopAircraft() {
    fdm_.SetPropertyValue("propulsion/engine/set-running", 0);
    fdm_.SetPropertyValue("propulsion/starter_cmd", 0);
    fdm_.SetPropertyValue("fcs/mixture-cmd-norm", 0.0);
    fdm_.SetPropertyValue("propulsion/magneto_cmd", 0);
    engineOn = 0;
}

void Aircraft::adjustFCS(std::unique_ptr<FcsStrategy> &&strategy, double value) {
   fcsStrategy_ = std::move(strategy);

    if (fcsStrategy_) {
        fcsStrategy_->adjustValue(fdm_, value);
    } else {
        throw std::runtime_error("Bad strategy was set");
    }
}

void Aircraft::resetFCS() {
        fdm_.SetPropertyValue("fcs/throttle-cmd-norm", 0.0);
        fdm_.SetPropertyValue("fcs/elevator-cmd-norm", 0.0);
        fdm_.SetPropertyValue("fcs/rudder-cmd-norm", 0.0);
        fdm_.SetPropertyValue("fcs/aileron-cmd-norm", 0.0);
}