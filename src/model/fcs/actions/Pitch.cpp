//
// Created by jay on 6/27/26.
//

#include "Pitch.h"

void Pitch::adjustValue(JSBSim::FGFDMExec &fdm, double delta) {
    double current = fdm.GetPropertyValue(FCS::elevator.data());
    double next = current + delta;
    if (next > 1.0) {
        next = 1.0;
    } else if (next < 0.0) {
        next = -1.0;
    }
    fdm.SetPropertyValue(FCS::elevator.data(), next);
}

void Pitch::setValue(JSBSim::FGFDMExec &fdm, double value) {
    fdm.SetPropertyValue(FCS::elevator.data(), value);
}
