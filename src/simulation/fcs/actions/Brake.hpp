//
// Created by jay on 6/27/26.
//

#ifndef JSB_BRAKE_H
#define JSB_BRAKE_H
#include "../FcsStrategy.h"

/**
 * FCS Brake controls.
 */
class Brake : public FcsStrategy {
public:
    ~Brake() override = default;
    void adjustValue(JSBSim::FGFDMExec &fdm, double delta) override {
        double isOn = fdm.GetPropertyValue(FCS::brake_center.data());

        if (!isOn) {
            fdm.SetPropertyValue(FCS::brake_left.data(), 1.0);
            fdm.SetPropertyValue(FCS::brake_right.data(), 1.0);
            fdm.SetPropertyValue(FCS::brake_center.data(), 1.0);
        } else {
            fdm.SetPropertyValue(FCS::brake_left.data(), 0.0);
            fdm.SetPropertyValue(FCS::brake_right.data(), 0.0);
            fdm.SetPropertyValue(FCS::brake_center.data(), 0.0);
        }
    };

    void setValue(JSBSim::FGFDMExec &fdm, double value) override {
        fdm.SetPropertyValue(FCS::brake_left.data(), value);
        fdm.SetPropertyValue(FCS::brake_right.data(), value);
        fdm.SetPropertyValue(FCS::brake_center.data(), value);
    }
};


#endif //JSB_BRAKE_H
