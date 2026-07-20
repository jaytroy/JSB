//
// Created by jay on 6/26/26.
//

#include "Aircraft.h"

#include <JSBSim/FGFDMExec.h>
#include <models/FGPropagate.h>

#include "fcs/FcsStrategy.h"
#include "shared/RendererPayload.hpp"

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
void Aircraft::resetFCS() const {
        fdm_.SetPropertyValue("fcs/elevator-cmd-norm", 0.0);
        fdm_.SetPropertyValue("fcs/rudder-cmd-norm", 0.0);
        fdm_.SetPropertyValue("fcs/aileron-cmd-norm", 0.0);
}

void Aircraft::updateValues() {
    airspeed_ = fdm_.GetPropertyValue("velocities/vc-kts");
    posN_ = fdm_.GetPropertyValue("position/from-start-neu-n-ft");
    posE_ = fdm_.GetPropertyValue("position/from-start-neu-e-ft");
    posU_ = fdm_.GetPropertyValue("position/from-start-neu-u-ft");
    rpm_ = fdm_.GetPropertyValue("propulsion/engine/engine-rpm");
    heading_ = fdm_.GetPropertyValue("attitude/heading-true-rad") * (180.0 / 3.141592653589793238463);
    brake_ = fdm_.GetPropertyValue("fcs/center-brake-cmd-norm");
    roll_ = fdm_.GetPropertyValue("attitude/roll-rad") * (180.0 / 3.141592653589793238463);
    throttle_ = fdm_.GetPropertyValue("fcs/throttle-cmd-norm");
    pitch_ = fdm_.GetPropertyValue("attitude/pitch-rad") * (180.0 / 3.141592653589793238463);
}


void Aircraft::appendDataTo(RendererPayload& rendererPayload) const {
    rendererPayload.north = posN_;
    rendererPayload.east = posE_;
    rendererPayload.up = posU_;
    rendererPayload.heading = heading_;
    rendererPayload.airspeed = airspeed_;
    rendererPayload.throttle = throttle_;
    rendererPayload.rpm = rpm_;
    rendererPayload.pitch = pitch_;
    rendererPayload.roll = roll_;
    rendererPayload.brake = brake_;
}
