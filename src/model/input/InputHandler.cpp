//
// Created by jay on 7/7/26.
//

#include "InputHandler.h"

#include <FGFDMExec.h>
#include <ncurses.h>

#include "InputDevice.h"
#include "../../input/Joystick.h"

InputHandler::InputHandler() {
    strategies_ = FcsStrategyFactory::createAll();

    //Set up input
    inputDevices_.push_back(std::make_unique<Joystick>());
}

int InputHandler::handleInput(JSBSim::FGFDMExec &fdm) {
    //Keyboard
    int ch;
    while ((ch = getch()) != ERR) {
        if (ch == 27) {
            return 0;
        }

        auto res = keyToCommand_.find(ch);
        if (res != keyToCommand_.end()) {
            auto command = commandHandler_.find(res->second);
            if (command != commandHandler_.end()) {
                FcsBinding &binding = command->second;
                strategies_[binding.strategyKey]->adjustValue(fdm, binding.delta);
            }
        }
    }

    handleJoystick(fdm);

    return 1;
}

/**
 * These currently only handle FCS. Need to expand to work with other bindings.
 * @param fdm The FDM instance.
 */
void InputHandler::handleJoystick(JSBSim::FGFDMExec &fdm) {
    for (std::unique_ptr<InputDevice> &device: inputDevices_) {
        //Currently only one device
        InputEvent event;
        device->pollEvents(event);

        FcsBinding fcs;

        if (event.type == JOYAXIS) {
            switch (event.info) {
                case 0:
                    fcs.strategyKey = "roll";
                    break;
                case 1:
                    fcs.strategyKey = "pitch";
                    break;
                case 2:
                    fcs.strategyKey = "yaw";
                    break;
                default:
                    //Other axis
                    break;
            }

            fcs.delta = event.delta;
            strategies_[fcs.strategyKey]->adjustValue(fdm, fcs.delta);
        } else if (event.type == JOYBTN) {
            //Develop button handling logic
            //Bindings for control systems can be included here
            std::cout << "Button pressed\n";
        }

    }
}
