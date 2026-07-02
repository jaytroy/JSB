//
// Created by jay on 6/27/26.
//

#ifndef JSB_INPUTDEVICE_H
#define JSB_INPUTDEVICE_H

struct InputEvent {
    int code;
};

class InputDevice {
public:
    virtual ~InputDevice() = default;
    virtual bool pollEvents(std::vector<InputEvent> &outEvent) = 0;
};


#endif //JSB_INPUTDEVICE_H
