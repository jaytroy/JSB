//
// Created by jay on 6/27/26.
//

#include "Yaw.h"

void Yaw::adjustValue(JSBSim::FGFDMExec &fdm, double delta) {
    double current = fdm.GetPropertyValue(FCS::rudder.data());
    double next = current + delta;
    if (next > 1.0) {
        next = 1.0;
    } else if (next < -1.0) {
        next =-1.0;
    }
    fdm.SetPropertyValue(FCS::rudder.data(), next);
}

void Yaw::setValue(JSBSim::FGFDMExec &fdm, double value) {
    fdm.SetPropertyValue(FCS::rudder.data(), value);
}
