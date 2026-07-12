//
// Created by jay on 6/26/26.
//

#ifndef JSB_STRATEGY_H
#define JSB_STRATEGY_H
#include <stdexcept>
#include <string>
#include <JSBSim/FGFDMExec.h>


/**
 * @brief Abstract class defining functionality for FCS commands using the strategy design pattern.
 */
class FcsStrategy { //Rename this to smt more fitting or make another class
public:
    virtual ~FcsStrategy() = default;

    /**
     * AdjustValue is used if we want to change the throttle through discrete (on-off) events.
     * For example, when the game is controlled via keyboard, we want to be able to
     * increment values based on the current ones.
     * @param fdm The fdm instance.
     * @param delta The incremental change.
     */
    virtual void adjustValue(JSBSim::FGFDMExec &fdm, double delta) = 0;

    /**
     * SetValue is used if we want to change the throttle through continuous (absolute) events.
     * For example, when the game is controlled via joystick, we want to be able to
     * set values directly based on where the joystick axes point.
     * @param fdm The fdm instance.
     * @param value The absolute change.
     */
    virtual void setValue(JSBSim::FGFDMExec &fdm, double value) {}
};

namespace FCS { //Should this be here?
    static constexpr std::string_view throttle = "fcs/throttle-cmd-norm";
    static constexpr std::string_view rudder = "fcs/rudder-cmd-norm";
    static constexpr std::string_view aileron = "fcs/aileron-cmd-norm";
    static constexpr std::string_view elevator = "fcs/elevator-cmd-norm";
    static constexpr std::string_view brake_left = "fcs/left-brake-cmd-norm";
    static constexpr std::string_view brake_right = "fcs/right-brake-cmd-norm";
    static constexpr std::string_view brake_center = "fcs/center-brake-cmd-norm";
    static constexpr std::string_view engine = "propulsion/engine/set-running";
    static constexpr std::string_view pitch_trim = "fcs/pitch-trim-cmd-norm";
    static constexpr std::string_view roll_trim = "fcs/roll-trim-cmd-norm";
    static constexpr std::string_view yaw_trim = "fcs/yaw-trim-cmd-norm";
}


#endif //JSB_STRATEGY_H
