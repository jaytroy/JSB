//
// Created by jay on 7/9/26.
//

#ifndef JSB_TRIM_H
#define JSB_TRIM_H
#include <algorithm>
#include <cmath>
#include <numbers>

#include "../FcsStrategy.h"


class Trim : public FcsStrategy {
public:
    ~Trim() override = default;

    void adjustValue(JSBSim::FGFDMExec &fdm, const double delta) override {
        const double rad = delta * std::numbers::pi / 180.0;
        const double step = RATE * fdm.GetDeltaT();
        const double u = std::cos(rad) * step;
        const double r = std::sin(rad) * step;

        const double pitch_c = fdm.GetPropertyValue("fcs/pitch-trim-cmd-norm");
        const double roll_c = fdm.GetPropertyValue("fcs/roll-trim-cmd-norm");

        fdm.SetPropertyValue("fcs/pitch-trim-cmd-norm", std::clamp(pitch_c + u, -1.0, 1.0));
        fdm.SetPropertyValue("fcs/roll-trim-cmd-norm", std::clamp(roll_c + r, -1.0, 1.0));
    }

private:
    //Full trim range per second of held hat.
    static constexpr double RATE = 0.2;
};


#endif //JSB_TRIM_H
