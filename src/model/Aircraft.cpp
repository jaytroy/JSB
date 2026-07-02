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