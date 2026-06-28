//
// Created by jay on 6/26/26.
//

#include "Aircraft.h"

#include <FGFDMExec.h>
#include <stdexcept>
#include <models/FGPropagate.h>

#include "fcs/FcsStrategy.h"

/**
 * The aircraft constructor.
 * @param fdm The FDM instance.
 */
Aircraft::Aircraft(JSBSim::FGFDMExec &fdm)
    : fdm_(fdm) {}

/**
 * Starts the aircraft.
 * *** WILL BE REMOVED ***
 */
void Aircraft::startAircraft() {
    fdm_.SetPropertyValue("propulsion/engine/set-running", 1);
    fdm_.SetPropertyValue("propulsion/starter_cmd", 1);
    fdm_.SetPropertyValue("fcs/mixture-cmd-norm", 1.0);
    fdm_.SetPropertyValue("propulsion/magneto_cmd", 3);
    fdm_.SetPropertyValue("fcs/elevator-trim-cmd-norm", 0.2);
    engineOn = 1;
}

/**
 * Stops the aircraft.
 * *** WILL BE REMOVED ***
 */
void Aircraft::stopAircraft() {
    fdm_.SetPropertyValue("propulsion/engine/set-running", 0);
    fdm_.SetPropertyValue("propulsion/starter_cmd", 0);
    fdm_.SetPropertyValue("fcs/mixture-cmd-norm", 0.0);
    fdm_.SetPropertyValue("propulsion/magneto_cmd", 0);
    engineOn = 0;
}

/**
 * Resets FCS to prevent to prevent it "sticking" in one direction.
 * This makes controls game-like.
 */
void Aircraft::resetFCS() {
        fdm_.SetPropertyValue("fcs/throttle-cmd-norm", 0.0);
        fdm_.SetPropertyValue("fcs/elevator-cmd-norm", 0.0);
        fdm_.SetPropertyValue("fcs/rudder-cmd-norm", 0.0);
        fdm_.SetPropertyValue("fcs/aileron-cmd-norm", 0.0);
}