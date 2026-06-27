//
// Created by jay on 6/27/26.
//

#ifndef JSB_BRAKE_H
#define JSB_BRAKE_H
#include "../fcsStrategy.h"


class Brake : FcsStrategy {
public:
    ~Brake() override;
    void adjustValue(JSBSim::FGFDMExec fdm, double value) override;
};


#endif //JSB_BRAKE_H
