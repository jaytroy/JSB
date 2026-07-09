//
// Created by jay on 6/27/26.
//

#ifndef JSB_YAW_H
#define JSB_YAW_H
#include "../FcsStrategy.h"

/**
 * FCS Yaw controls.
 */
class Yaw : public FcsStrategy {
public:
    ~Yaw() override = default;

    void adjustValue(JSBSim::FGFDMExec &fdm, double delta) override {
        double current = fdm.GetPropertyValue(FCS::rudder.data());
        double next = current + delta;
        if (next > 1.0) {
            next = 1.0;
        } else if (next < -1.0) {
            next =-1.0;
        }
        fdm.SetPropertyValue(FCS::rudder.data(), next);
    }

    void setValue(JSBSim::FGFDMExec &fdm, double value) override {

    fdm.SetPropertyValue(FCS::rudder.data(), value);
    }
};


#endif //JSB_YAW_H
