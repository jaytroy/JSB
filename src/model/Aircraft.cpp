//
// Created by jay on 6/26/26.
//

#include "Aircraft.h"

#include <FGFDMExec.h>
#include <models/FGPropagate.h>

#include "fcs/FcsStrategy.h"

/**
 * The aircraft constructor.
 * @param fdm The FDM instance.
 */
Aircraft::Aircraft(JSBSim::FGFDMExec &fdm)
    : fdm_(fdm) {}

/**
 * Resets FCS to prevent to prevent it "sticking" in one direction.
 * This makes controls game-like.
 */
void Aircraft::resetFCS() {
        fdm_.SetPropertyValue("fcs/elevator-cmd-norm", 0.0);
        fdm_.SetPropertyValue("fcs/rudder-cmd-norm", 0.0);
        fdm_.SetPropertyValue("fcs/aileron-cmd-norm", 0.0);
}

void Aircraft::updateValue() {
    airspeed = fdm_.GetPropertyValue("velocities/vc-kts");
    posN = fdm_.GetPropertyValue("position/from-start-neu-n-ft");
    posE = fdm_.GetPropertyValue("position/from-start-neu-e-ft");
    posU = fdm_.GetPropertyValue("position/from-start-neu-u-ft");
    rpm = fdm_.GetPropertyValue("propulsion/engine/engine-rpm");
    heading = fdm_.GetPropertyValue("attitude/heading-true-rad") * (180.0 / 3.141592653589793238463);
    brake = fdm_.GetPropertyValue("fcs/center-brake-cmd-norm");
    roll = fdm_.GetPropertyValue("attitude/roll-rad");
    throttle = fdm_.GetPropertyValue("fcs/throttle-cmd-norm");
    pitch = fdm_.GetPropertyValue("fcs/pitch-cmd-norm");
}