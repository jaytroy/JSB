//
// Created by jay on 6/27/26.
//

#include "Pitch.h"

void Pitch::adjustValue(JSBSim::FGFDMExec fdm, double value) {
    fdm.adjustValue(FCS::elevator, value);
}
