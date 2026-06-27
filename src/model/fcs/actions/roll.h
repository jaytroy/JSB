//
// Created by jay on 6/27/26.
//

#ifndef JSB_ROLL_H
#define JSB_ROLL_H
#include "../fcsStrategy.h"


class Roll : public FcsStrategy {
public:
    ~Roll() override;
    void adjustValue(JSBSim::FGFDMExec fdm, double value) override;
};


#endif //JSB_ROLL_H
