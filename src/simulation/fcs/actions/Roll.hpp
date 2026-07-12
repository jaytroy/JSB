//
// Created by jay on 6/27/26.
//

#ifndef JSB_ROLL_H
#define JSB_ROLL_H
#include "../FcsStrategy.h"

/**
 * FCS Roll controls.
 */
class Roll : public FcsStrategy {
public:
    ~Roll() override = default;
    void adjustValue(JSBSim::FGFDMExec &fdm, double delta) override {
        double current = fdm.GetPropertyValue(FCS::aileron.data());
        double next = current + delta;
        if (next > 1.0) {
            next = 1.0;
        } else if (next < -1.0) {
            next = -1.0;
        }
        fdm.SetPropertyValue(FCS::aileron.data(), next);
    }

    void setValue(JSBSim::FGFDMExec &fdm, double value) override {
        fdm.SetPropertyValue(FCS::aileron.data(), -value);
    };
};


#endif //JSB_ROLL_H
