//
// Created by jay on 7/16/26.
//

#ifndef JSB_INPUTDEVICEMANAGER_H
#define JSB_INPUTDEVICEMANAGER_H
#include "KeyboardSink.h"
#include "../SDL/EventPump.h"


class InputDeviceManager {
public:
    InputDeviceManager(Window& window) { //Passing window in is not my favorite thing. Is there a better way?
        pump_.addSink(&keyboardSink_);
        pump_.addSink(window.getGfxSink());

        axisDevices_ = InputDeviceFactory::createAxisDevices();
    }

    bool pump(std::vector<OutCommand>& outCommands) {
        outCommands.clear();

        outData = keyboardSink_.drain(); //Needs an implementation of char to cmd

        for (auto& [id, device] : axisDevices_) {
             device->sampleState(outCommands);
        }

        return pump_.pump();
    }

    std::vector<int> outData;

private:
    EventPump pump_;
    KeyboardSink keyboardSink_; //This needs to be polymorphized
    std::unordered_map<int, std::unique_ptr<AxisDevice>> axisDevices_;
    std::vector<OutCommand> outCommands;
};


#endif //JSB_INPUTDEVICEMANAGER_H
