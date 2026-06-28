//
// Created by jay on 6/27/26.
//

#include "Pitch.h"

void Pitch::adjustValue(JSBSim::FGFDMExec &fdm, double value) {
    double current = fdm.GetPropertyValue(FCS::elevator.data());
    double next = current + value;
    if (next > 1.0) {
        next = 1.0;
    } else if (next < 0.0) {
        next = -1.0;
    }
    fdm.SetPropertyValue(FCS::elevator.data(), next);
}
