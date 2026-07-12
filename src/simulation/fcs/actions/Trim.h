//
// Created by jay on 7/9/26.
//

#ifndef JSB_TRIM_H
#define JSB_TRIM_H
#include "../FcsStrategy.h"


class Trim : public FcsStrategy {
public:
    ~Trim() override = default;
    void adjustValue(JSBSim::FGFDMExec &fdm, double delta) override {
    }
};


#endif //JSB_TRIM_H
