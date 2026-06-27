//
// Created by jay on 6/27/26.
//

#include "Brake.h"

void Brake::adjustValue(JSBSim::FGFDMExec fdm, double value) {
    fdm.SetPropertyValue("fcs/left-brake-cmd-norm", 1.0);
    fdm.SetPropertyValue("fcs/right-brake-cmd-norm", 1.0);
    fdm.SetPropertyValue("fcs/center-brake-cmd-norm", 1.0);}
