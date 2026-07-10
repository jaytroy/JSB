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

struct ControlEvent { //this currently holds logic for joystick (T16000). This needs to be able to handle other input devices as well
    InputType type;
    double roll;
    double pitch;
    double yaw;
    double slider;
};

/**
 * This handles continuous events, like joystick.
 * Events here are taken directly from the device, bypassing an event pump.
 */
class InputDevice {
public:
    virtual ~InputDevice() = default;
    virtual void sampleState(ControlEvent& out) = 0;
};

#endif //JSB_INPUTDEVICE_H
