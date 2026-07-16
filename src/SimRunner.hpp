//
// Created by jay on 7/12/26.
//

#ifndef JSB_SIMRUNNER_H
#define JSB_SIMRUNNER_H

#include <thread>

#include "gfx/Window.h"
#include "input/InputDeviceFactory.hpp"
#include "input/InputDeviceManager.hpp"
#include "input/KeyboardSink.h"
#include "SDL/EventPump.h"
#include "simulation/Simulation.h"

/**
 * SimRunner is a proxy managing and running all parts of the simulator.
 * It orchestrates everything, ensuring packages stay separate from each other.
 */
class SimRunner {
public:
    SimRunner(const char* aircraftModel, const char* resetFile) : sim_(aircraftModel, resetFile), inputManager_(window_) {
        dt_ = sim_.getDt();
    }

    void run() {
        while (inputManager_.pump(outCommands_)) {
            //This should have more logic than a vector of doubles
            std::vector<double> rendererPayload = sim_.run(inputManager_.outData, outCommands_);

            window_.renderFrame(rendererPayload);

            std::this_thread::sleep_for(std::chrono::duration<double>(dt_));
        }

        window_.cleanup();
        std::cout << "Exited successfully" << std::endl;
    }

    void updateSim() {
        //TODO: make sim hard data updatable
    }

private:
    std::vector<OutCommand> outCommands_;
    InputDeviceManager inputManager_;
    Simulation sim_;
    Window window_;
    double dt_;
};

#endif //JSB_SIMRUNNER_H
