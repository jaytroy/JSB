//
// Created by jay on 6/27/26.
//

#include "yaw.h"

void Yaw::adjustValue(JSBSim::FGFDMExec fdm, double value) {
    fdm.SetPropertyValue(FCS::rudder.data(), value);
}
