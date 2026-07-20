//
// Created by jay on 7/16/26.
//

#ifndef JSB_INPUTDEVICEMANAGER_H
#define JSB_INPUTDEVICEMANAGER_H
#include "InputDeviceFactory.hpp"
#include "KeyboardSink.hpp"
#include "../SDL/EventPump.h"


class InputDeviceManager {
public:
    explicit InputDeviceManager(Window& window) { //Passing window in is not my favorite thing. Is there a better way?
        //Create axis devices
        axisDevices_ = InputDeviceFactory::createAxisDevices();
        for (auto& device : axisDevices_) {
            if (auto* sink = dynamic_cast<EventSink*>(device.get())) {
                pump_.addSink(sink);
                sinks_.push_back(sink);
                std::cout << "Added sink" << std::endl;
            }
        }

        //Then assign base sinks
        //These need to be polymorphized
        pump_.addSink(&keyboardSink_);
        pump_.addSink(window.getGfxSink());
    }

    bool pump(std::vector<OutCommand>& outCommands) {
        outCommands.clear();

        keyboardSink_.drain(outCommands); //Again, should be part of sinks
        for (auto& sink : sinks_) {
            sink->drain(outCommands);
        }

        for (auto& device : axisDevices_) {
             device->sampleState(outCommands);
        }

        return pump_.pump();
    }

private:
    EventPump pump_;
    std::vector<EventSink*> sinks_;
    KeyboardSink keyboardSink_;
    std::vector<std::unique_ptr<AxisDevice>> axisDevices_;
};


#endif //JSB_INPUTDEVICEMANAGER_H
