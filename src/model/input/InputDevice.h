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
 * Abstract class (interface) defining input device functionality.
 */
class InputDevice {
public:
    virtual ~InputDevice() = default;
    virtual bool pollEvents(InputEvent &outEvent) = 0; //Currently holds 1 outevent. Turn into vector to make more?
};

#endif //JSB_INPUTDEVICE_H
