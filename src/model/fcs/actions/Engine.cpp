//
// Created by jay on 7/1/26.
//

#include "Engine.h"

/**
 * This current acts as a full startup, not just the engine.
 * @param fdm
 * @param value
 */
void Engine::adjustValue(JSBSim::FGFDMExec &fdm, double value) {
    double isOn = fdm.GetPropertyValue(FCS::engine.data());

    if (!isOn) {
        fdm.SetPropertyValue("propulsion/engine/set-running", 1);
        fdm.SetPropertyValue("propulsion/starter_cmd", 1);
        fdm.SetPropertyValue("fcs/mixture-cmd-norm", 1.0);
        fdm.SetPropertyValue("propulsion/magneto_cmd", 3);
        fdm.SetPropertyValue("fcs/elevator-trim-cmd-norm", 0.2); //Technically shouldn't be here
    } else {
        fdm.SetPropertyValue("propulsion/engine/set-running", 0);
        fdm.SetPropertyValue("propulsion/starter_cmd", 0);
        fdm.SetPropertyValue("fcs/mixture-cmd-norm", 0.0);
        fdm.SetPropertyValue("propulsion/magneto_cmd", 0);
    }
}
