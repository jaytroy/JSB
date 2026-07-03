//
// Created by jay on 6/27/26.
//

#ifndef JSB_INPUTDEVICE_H
#define JSB_INPUTDEVICE_H

struct InputEvent {
    int keyCode;
    int pitch;
    int roll;
    int yaw;
};

/**
 * Abstract class defining input functionality.
 * Currently works with keyboard.
 */
class InputDevice {
public:
    virtual ~InputDevice() = default;
    virtual bool pollEvents(std::vector<InputEvent> &outEvent) = 0; //Does this need to be an array? Liekly need just the latest.
};


#endif //JSB_INPUTDEVICE_H
