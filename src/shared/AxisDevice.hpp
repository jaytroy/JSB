//
// Created by jay on 6/27/26.
//

#ifndef JSB_INPUTDEVICE_H
#define JSB_INPUTDEVICE_H

#include <vector>
#include <algorithm>
#include <stdexcept>

#include "FcsCommand.h"

// SDL automatically auto-normalizes axes to 2^16 / 2 -> (32768)
// If SDL is dropped in the future, this will need to be updated
#define MAX 32767.0

/**
 * This handles continuous events, like joystick.
 * Events here are taken directly from the device, bypassing an event pump.
 */
class AxisDevice {
public:
    virtual ~AxisDevice() = default;

    /**
     * SampleState takes a sample of the control device's axis position when called.
     * This may include buttons and hats in the future.
     */
    virtual void sampleState(std::vector<OutCommand> &outCommands) = 0;

    /**
     * Normalizes raw joystick values into the format used by JSBSim: [-1,1].
     * @param value The value to be normalized.
     * @return The normalized value.
     */
    static double normalize(double value, int type) {
        //considering this is a shared package,
        //type should maybe not be here as it loosely couples this to input
        //consider moving it into Joystick directly
        switch (type) {
            case 0: return std::clamp(value /= MAX, -1.0, 1.0);
            case 1: return std::clamp((value + MAX) / (2*MAX), -1.0, 1.0);
        default: throw std::runtime_error("Something failed in normalization");

        }
    }
};

#endif //JSB_INPUTDEVICE_H
