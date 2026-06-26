//
// Created by jay on 6/26/26.
//

#ifndef JSB_THROTTLE_H
#define JSB_THROTTLE_H
#include "fcsStrategy.h"


class Throttle : public FcsStrategy {
    ~Throttle() override;

    void adjustValue(std::string target, double value) override;

    Throttle();
};


#endif //JSB_THROTTLE_H
