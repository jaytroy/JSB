//
// Created by jay on 6/27/26.
//

#include "Brake.h"

void Brake::adjustValue(JSBSim::FGFDMExec &fdm, double value) {
    double current = fdm.GetPropertyValue(FCS::brake_center.data());

    printf("Brake is %lf", current);

    if (current == 0.0) {
        fdm.SetPropertyValue(FCS::brake_left.data(), 1.0);
        fdm.SetPropertyValue(FCS::brake_right.data(), 1.0);
        fdm.SetPropertyValue(FCS::brake_center.data(), 1.0);
    } else {
        fdm.SetPropertyValue(FCS::brake_left.data(), 0.0);
        fdm.SetPropertyValue(FCS::brake_right.data(), 0.0);
        fdm.SetPropertyValue(FCS::brake_center.data(), 0.0);
    }


}