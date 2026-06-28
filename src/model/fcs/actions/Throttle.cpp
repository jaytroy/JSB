//
// Created by jay on 6/26/26.
//

#include "Throttle.h"

void Throttle::adjustValue(JSBSim::FGFDMExec &fdm, double value) {
    double current = fdm.GetPropertyValue(FCS::throttle.data());
    double next = current + value;
    if (next > 1.0) {
        next = 1.0;
    } else if (next < 0.0) {
        next = 0.0;
    }

    fdm.SetPropertyValue(FCS::throttle.data(), next);
}
