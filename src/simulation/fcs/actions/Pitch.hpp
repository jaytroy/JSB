//
// Created by jay on 6/27/26.
//

#ifndef JSB_PITCH_H
#define JSB_PITCH_H
#include "../FcsStrategy.h"

/**
 * FCS Pitch controls.
 */
class Pitch : public FcsStrategy {
public:
    ~Pitch() override = default;
    void adjustValue(JSBSim::FGFDMExec &fdm, double delta) override {
        double current = fdm.GetPropertyValue(FCS::elevator.data());
        double next = current + delta;
        if (next > 1.0) {
            next = 1.0;
        } else if (next < 0.0) {
            next = -1.0;
        }
        fdm.SetPropertyValue(FCS::elevator.data(), next);
    }

    void setValue(JSBSim::FGFDMExec &fdm, double value) override {
        fdm.SetPropertyValue(FCS::elevator.data(), value);
    }
};


#endif //JSB_PITCH_H
