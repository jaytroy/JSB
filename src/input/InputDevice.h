//
// Created by jay on 6/27/26.
//

#ifndef JSB_INPUTDEVICE_H
#define JSB_INPUTDEVICE_H

struct InputEvent {
    int code;
    bool pressed;
};

/**
 * Abstract class defining input functionality.
 * Currently works with keyboard.
 */
class InputDevice {
public:
    virtual ~InputDevice() = default;
    virtual bool pollEvent(InputEvent &outEvent) = 0;
};


#endif //JSB_INPUTDEVICE_H
