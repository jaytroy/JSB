//
// Created by jay on 6/27/26.
//

#ifndef JSB_PITCH_H
#define JSB_PITCH_H
#include "../FcsStrategy.h"


class Pitch : public FcsStrategy {
public:
    ~Pitch() override;
    void adjustValue(JSBSim::FGFDMExec fdm, double value) override;
};


#endif //JSB_PITCH_H
