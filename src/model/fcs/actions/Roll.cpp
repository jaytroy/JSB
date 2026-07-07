//
// Created by jay on 6/27/26.
//

#include "Roll.h"

void Roll::adjustValue(JSBSim::FGFDMExec &fdm, double delta) {
    double current = fdm.GetPropertyValue(FCS::aileron.data());
    double next = current + delta;
    if (next > 1.0) {
        next = 1.0;
    } else if (next < -1.0) {
        next = -1.0;
    }
    fdm.SetPropertyValue(FCS::aileron.data(), next);
}

void Roll::setValue(JSBSim::FGFDMExec &fdm, double value) {
    fdm.SetPropertyValue(FCS::aileron.data(), value);
}
