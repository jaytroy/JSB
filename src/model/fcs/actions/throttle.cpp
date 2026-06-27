//
// Created by jay on 6/26/26.
//

#include "throttle.h"

void Throttle::adjustValue(JSBSim::FGFDMExec fdm, double value) {
        fdm.SetPropertyValue(FCS::throttle.data(), value);
}
