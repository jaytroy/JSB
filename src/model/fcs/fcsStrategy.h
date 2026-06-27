//
// Created by jay on 6/26/26.
//

#ifndef JSB_STRATEGY_H
#define JSB_STRATEGY_H
#include <string>
#include <JSBSim/FGFDMExec.h>


class FcsStrategy {
public:
    virtual ~FcsStrategy() = default;
    virtual void adjustValue(JSBSim::FGFDMExec fdm, double value);
};

enum class ControlChannel {
    Elevator,
    Aileron,
    Throttle,
    Rudder,
};

namespace FCS {
    static constexpr std::string_view throttle = "fcs/throttle-cmd-norm";
    static constexpr std::string_view rudder = "fcs/rudder-cmd-norm";
    static constexpr std::string_view aileron = "fcs/aileron-cmd-norm";
    static constexpr std::string_view elevator = "fcs/elevator-cmd-norm";
}

#endif //JSB_STRATEGY_H
