//
// Created by jay on 6/26/26.
//

#ifndef JSB_THROTTLE_H
#define JSB_THROTTLE_H
#include "../FcsStrategy.h"

/**
 * FCS Throttle controls.
 */
class Throttle : public FcsStrategy {
public:
    ~Throttle() override = default;

    void adjustValue(JSBSim::FGFDMExec &fdm, double delta) override {
        double current = fdm.GetPropertyValue(FCS::throttle.data());
        double next = current + delta;
        if (next > 1.0) {
            next = 1.0;
        } else if (next < 0.0) {
            next = 0.0;
        }

        fdm.SetPropertyValue(FCS::throttle.data(), next);
    }

    void setValue(JSBSim::FGFDMExec &fdm, double value) override {
        fdm.SetPropertyValue(FCS::throttle.data(), value);
    }
};


#endif //JSB_THROTTLE_H
