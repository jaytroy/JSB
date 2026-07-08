//
// Created by jay on 7/7/26.
//

#include "InputHandler.h"

#include <FGFDMExec.h>

#include "InputDevice.h"
#include "../../input/Joystick.h"
#include "../fcs/FcsStrategyFactory.h"

InputHandler::InputHandler() {
    strategies_ = FcsStrategyFactory::createAll();

    //Set up input
    try {
        inputDevices_.push_back(std::make_unique<Joystick>());
    } catch (const std::runtime_error &e) {
        std::cout << "Did not find a joystick\n";
    }
}

int InputHandler::handleInput(JSBSim::FGFDMExec &fdm) {

    for (std::unique_ptr<InputDevice> &device: inputDevices_) {
        //This only works with joystick atm. Needs a refactor
        ControlEvent event;
        device->sampleState(event);

        strategies_["roll"]->setValue(fdm, event.roll);
        strategies_["pitch"]->setValue(fdm, event.pitch);
        strategies_["yaw"]->setValue(fdm, event.yaw);
        strategies_["throttle"]->setValue(fdm, event.slider);
    }

    std::vector<FcsCommand> cmds;
    keyboardSink_.drain(cmds);
    for (FcsCommand c : cmds) {
        auto b = commandHandler_.find(c);
        if (b != commandHandler_.end()) {
            FcsBinding &binding = b->second;
            strategies_[binding.strategyKey]->adjustValue(fdm, binding.delta);
        }
    }

    return 1;
}

void InputHandler::registerSinks(EventPump &pump) {
    pump.addSink(&keyboardSink_);

    for (auto& device : inputDevices_) {
        if (auto* sink = dynamic_cast<EventSink*>(device.get()))
            pump.addSink(sink);
    }
}

