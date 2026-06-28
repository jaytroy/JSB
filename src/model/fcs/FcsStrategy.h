//
// Created by jay on 6/26/26.
//

#ifndef JSB_STRATEGY_H
#define JSB_STRATEGY_H
#include <string>
#include <JSBSim/FGFDMExec.h>


/**
 * @brief Defines functionality for FCS commands using the strategy design pattern.
 */
class FcsStrategy {
public:
    virtual ~FcsStrategy() = default;
    virtual void adjustValue(JSBSim::FGFDMExec &fdm, double value) = 0;
};

enum class ControlChannel {
    Elevator,
    Aileron,
    Throttle,
    Rudder,
};

namespace FCS { //Should this be here?
    static constexpr std::string_view throttle = "fcs/throttle-cmd-norm";
    static constexpr std::string_view rudder = "fcs/rudder-cmd-norm";
    static constexpr std::string_view aileron = "fcs/aileron-cmd-norm";
    static constexpr std::string_view elevator = "fcs/elevator-cmd-norm";
    static constexpr std::string_view brake_left = "fcs/left-brake-cmd-norm";
    static constexpr std::string_view brake_right = "fcs/right-brake-cmd-norm";
    static constexpr std::string_view brake_center = "fcs/center-brake-cmd-norm";
}

#endif //JSB_STRATEGY_H
