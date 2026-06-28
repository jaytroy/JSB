//
// Created by jay on 6/27/26.
//

#ifndef JSB_FCSCOMMAND_H
#define JSB_FCSCOMMAND_H

struct FcsBinding {
    std::string strategyKey;
    double delta;
};

/**
 * An enum class for all possible FCS commands.
 * Will expand as sim expands.
 */
enum class FcsCommand {
    ThrottleUp, ThrottleDown,
    PitchUp, PitchDown,
    RollLeft, RollRight,
    YawLeft, YawRight,
    Start, Stop,
    ToggleBrake,
};


#endif //JSB_FCSCOMMAND_H
