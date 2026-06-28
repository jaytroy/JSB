//
// Created by jay on 6/27/26.
//

#include "Roll.h"

void Roll::adjustValue(JSBSim::FGFDMExec &fdm, double value) {
    double current = fdm.GetPropertyValue(FCS::aileron.data());
    double next = current + value;
    if (next > 1.0) {
        next = 1.0;
    } else if (next < -1.0) {
        next = -1.0;
    }
    fdm.SetPropertyValue(FCS::aileron.data(), next);
}
