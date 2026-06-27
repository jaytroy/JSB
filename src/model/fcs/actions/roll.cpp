//
// Created by jay on 6/27/26.
//

#include "roll.h"

void Roll::adjustValue(JSBSim::FGFDMExec fdm, double value) {
    fdm.SetPropertyValue(FCS::aileron.data(), value);
}
