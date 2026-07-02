//
// Created by jay on 6/27/26.
//

#ifndef JSB_PITCH_H
#define JSB_PITCH_H
#include "../FcsStrategy.h"

/**
 * FCS Pitch controls.
 */
class Pitch : public FcsStrategy {
public:
    ~Pitch() override = default;
    void adjustValue(JSBSim::FGFDMExec &fdm, double value) override;
};


#endif //JSB_PITCH_H
