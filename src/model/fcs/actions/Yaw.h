//
// Created by jay on 6/27/26.
//

#ifndef JSB_YAW_H
#define JSB_YAW_H
#include "../FcsStrategy.h"


class Yaw : public FcsStrategy {
public:
    ~Yaw() override = default;

    void adjustValue(JSBSim::FGFDMExec &fdm, double value) override;
};


#endif //JSB_YAW_H
