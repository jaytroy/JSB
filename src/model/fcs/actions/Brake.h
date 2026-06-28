//
// Created by jay on 6/27/26.
//

#ifndef JSB_BRAKE_H
#define JSB_BRAKE_H
#include "../FcsStrategy.h"


class Brake : public FcsStrategy {
public:
    ~Brake() override = default;
    void adjustValue(JSBSim::FGFDMExec &fdm, double value) override;
};


#endif //JSB_BRAKE_H
