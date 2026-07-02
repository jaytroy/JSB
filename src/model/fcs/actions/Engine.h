//
// Created by jay on 7/1/26.
//

#ifndef JSB_ENGINE_H
#define JSB_ENGINE_H
#include "../FcsStrategy.h"

/**
 * The engine class currently controls the statrtup sequence.
 */
class Engine : public FcsStrategy {
public:
    ~Engine() override = default;
    void adjustValue(JSBSim::FGFDMExec &fdm, double value) override;
};


#endif //JSB_ENGINE_H
