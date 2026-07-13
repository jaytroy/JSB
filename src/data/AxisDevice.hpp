//
// Created by jay on 6/27/26.
//

#ifndef JSB_INPUTDEVICE_H
#define JSB_INPUTDEVICE_H

enum InputType { // Move this into the class?
    JOYAXIS,
    THROTTLE,
    CONTROLLER, //Future proofing
};

/**
 * This is currently used by what will eventually become client and server.
 * Currently, it's used to pass input data from the input package to simulation.
 * This is likely to be serialized in the future.
 */
struct ControlEvent { //this currently holds logic for joystick (T16000). This needs to be able to handle other input devices as well
    InputType type;
    double roll;
    double pitch;
    double yaw;
    double slider;
};

// 2^16 / 2 denotes max movement (32768) for T16000
// SDL (allegedly) supports this for input devices from all vendors
// TODO: verify that
#define MAX 32768.0

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
     * @param out The result of the sampling.
     */
    virtual void sampleState(ControlEvent &out) = 0;

    /**
     * Normalizes raw joystick values into the format used by JSBSim: [-1,1].
     * @param value The value to be normalized.
     * @return The normalized value.
     */
    static double normalize(double value) {  return value /= MAX; }
};

#endif //JSB_INPUTDEVICE_H
