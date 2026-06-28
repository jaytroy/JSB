//
// Created by jay on 6/26/26.
//

#ifndef JSB_THROTTLE_H
#define JSB_THROTTLE_H
#include "../FcsStrategy.h"


class Throttle : public FcsStrategy {
public:
    ~Throttle() override = default;

    void adjustValue(JSBSim::FGFDMExec &fdm, double value) override;
};


#endif //JSB_THROTTLE_H
