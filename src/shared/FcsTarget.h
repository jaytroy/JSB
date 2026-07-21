//
// Created by jay on 7/16/26.
//

#ifndef JSB_FCSTARGET_H
#define JSB_FCSTARGET_H
#include "FcsCommand.h"

/**
 * Contains all possible FCS systems.
 * FcsTarget is 1:N with FcsCommand.
 */
class FcsTarget {
    enum Value {
        None,
        Throttle, Pitch, Yaw, Roll, Brake, Engine, Trim,
    };

    /**
    * This casts an FCS Command down to an FCS Target system.
    * TODO: There needs to be some logic here deciding if this is a continuous or a discrete event (right?)
    * @param cmd The FCS Command to be casted down.
    * @return The targeted FCS system.
    */
    static Value targetOf(const FcsCommand::Value cmd) {
        switch (cmd) {
            case FcsCommand::ThrottleUp:
            case FcsCommand::Throttle:
            case FcsCommand::ThrottleDown: return Throttle;
            case FcsCommand::Pitch:
            case FcsCommand::PitchUp:
            case FcsCommand::PitchDown:    return Pitch;
            case FcsCommand::Roll:
            case FcsCommand::RollLeft:
            case FcsCommand::RollRight:    return Roll;
            case FcsCommand::YawLeft:
            case FcsCommand::YawRight:
            case FcsCommand::Yaw:          return Yaw;
            case FcsCommand::ToggleBrake:  return Brake;
            case FcsCommand::ToggleEngine: return Engine;
            case FcsCommand::TrimUp:
            case FcsCommand::TrimRight:
            case FcsCommand::Trim:        return Trim;
            case FcsCommand::None: return None;
            default: return None;
        }
    }
};

#endif //JSB_FCSTARGET_H
