//
// Created by jay on 6/27/26.
//

#ifndef JSB_INPUTDEVICE_H
#define JSB_INPUTDEVICE_H

enum InputType { // Move this into the class?
    MOUSE,
    KEYBOARD,
    JOYAXIS,
    JOYBTN,
    THROTTLE,
    CONTROLLER, //Future proofing
};

struct InputEvent {
    InputType type;
    double delta;
    int info; //Info allows for any additional information. For example: which axis was activated
};

/**
 * This handles continuous events, like joystick.
 * Events here are taken directly from the device, bypassing an event pump.
 */
class InputDevice {
public:
    virtual ~InputDevice() = default;
    virtual void sampleState(InputEvent& out) = 0;
};

#endif //JSB_INPUTDEVICE_H
