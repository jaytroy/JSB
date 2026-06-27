//
// Created by jay on 6/27/26.
//

#include "pitch.h"

void Pitch::adjustValue(JSBSim::FGFDMExec fdm, double value) {
    fdm.adjustValue(FCS::elevator, value);
}
