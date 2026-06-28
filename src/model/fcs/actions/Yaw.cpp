//
// Created by jay on 6/27/26.
//

#include "Yaw.h"

void Yaw::adjustValue(JSBSim::FGFDMExec &fdm, double value) {
    double current = fdm.GetPropertyValue(FCS::rudder.data());
    double next = current + value;
    if (next > 1.0) {
        next = 1.0;
    } else if (next < -1.0) {
        next =-1.0;
    }
    fdm.SetPropertyValue(FCS::rudder.data(), next);
}
