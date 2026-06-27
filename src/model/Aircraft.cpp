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
Aircraft::Aircraft(const JSBSim::FGFDMExec &fdm)
    : fdm(fdm) {}

void Aircraft::startAircraft() {
    fdm.SetPropertyValue("propulsion/engine/set-running", 1);
    fdm.SetPropertyValue("propulsion/starter_cmd", 1);
    fdm.SetPropertyValue("fcs/mixture-cmd-norm", 1.0);
    fdm.SetPropertyValue("propulsion/magneto_cmd", 3);
    fdm.SetPropertyValue("fcs/elevator-trim-cmd-norm", 0.2);
    engineOn = 1;
}

void Aircraft::stopAircraft() {
    fdm.SetPropertyValue("propulsion/engine/set-running", 0);
    fdm.SetPropertyValue("propulsion/starter_cmd", 0);
    fdm.SetPropertyValue("fcs/mixture-cmd-norm", 0.0);
    fdm.SetPropertyValue("propulsion/magneto_cmd", 0);
    engineOn = 0;
}

void Aircraft::adjustFCS(std::unique_ptr<FcsStrategy> &&strategy, double value) {
   fcsStrategy_ = std::move(strategy);

    if (fcsStrategy_) {
        fcsStrategy_->adjustValue(fdm, value);
    } else {
        throw std::runtime_error("Bad strategy was set");
    }
}

void Aircraft::resetFCS() {
        fdm.SetPropertyValue("fcs/throttle-cmd-norm", 0.0);
        fdm.SetPropertyValue("fcs/elevator-cmd-norm", 0.0);
        fdm.SetPropertyValue("fcs/rudder-cmd-norm", 0.0);
        fdm.SetPropertyValue("fcs/aileron-cmd-norm", 0.0);
}