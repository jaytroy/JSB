//
// Created by jay on 7/16/26.
//

#ifndef JSB_FCSTARGET_H
#define JSB_FCSTARGET_H
#include "FcsCommand.h"


/**
 * Contains all possible FCS systems.
 * FcsCommand is 1:N with FcsStrategy.
 */
enum class FcsTarget {
    None,
    Throttle, Pitch, Yaw, Roll, Brake, Engine, Trim,
};

namespace Command {
    /**
     * This casts an FCS Command down to an FCS Target system.
     * TODO: There needs to be some logic here deciding if this is an axis or a discrete event
     * @param cmd The FCS Command to be casted down.
     * @return The targeted FCS system.
     */
    constexpr FcsTarget targetOf(const FcsCommand cmd) {
        switch (cmd) {
            case FcsCommand::ThrottleUp:
            case FcsCommand::Throttle:
            case FcsCommand::ThrottleDown: return FcsTarget::Throttle;
            case FcsCommand::Pitch:
            case FcsCommand::PitchUp:
            case FcsCommand::PitchDown:    return FcsTarget::Pitch;
            case FcsCommand::Roll:
            case FcsCommand::RollLeft:
            case FcsCommand::RollRight:    return FcsTarget::Roll;
            case FcsCommand::YawLeft:
            case FcsCommand::YawRight:
            case FcsCommand::Yaw:          return FcsTarget::Yaw;
            case FcsCommand::ToggleBrake:  return FcsTarget::Brake;
            case FcsCommand::ToggleEngine: return FcsTarget::Engine;
            case FcsCommand::TrimUp:
            case FcsCommand::TrimRight:
            case FcsCommand::Trim:        return FcsTarget::Trim;
            case FcsCommand::None: return FcsTarget::None;
            default: return FcsTarget::None;
        }
    }
}

#endif //JSB_FCSTARGET_H
