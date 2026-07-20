//
// Created by jay on 7/12/26.
//

#ifndef JSB_SIMRUNNER_H
#define JSB_SIMRUNNER_H

#include <thread>

#include "gfx/Window.h"
#include "input/InputDeviceManager.hpp"
#include "simulation/Simulation.h"

/**
 * SimRunner is a proxy managing and running all parts of the simulator.
 * It orchestrates everything, ensuring packages stay separate from each other.
 */
class SimRunner {
public:
    SimRunner(const char *aircraftModel, const char *resetFile) : inputManager_(window_), sim_(aircraftModel, resetFile) {
        dt_ = sim_.getDt();
    }

    void run() {
        while (inputManager_.pump(outCommands_)) {
            auto start = std::chrono::steady_clock::now();

            //This should have more logic than a vector of doubles
            RendererPayload p = sim_.run(outCommands_);

            //Add networking here
            //This should be sending to socket via json
            //socket_.send(p.toJson);
            window_.renderFrame(p);

            auto end = std::chrono::steady_clock::now();
            std::chrono::duration<double> elapsed = end - start;
            auto sleep = std::chrono::duration<double>(dt_) - elapsed;
            if (sleep > std::chrono::duration<double>::zero()) {
                std::this_thread::sleep_for(sleep);
            }
        }

        std::cout << "Exited successfully" << std::endl;
    }

private:
    Window window_;
    InputDeviceManager inputManager_;
    Simulation sim_;
    std::vector<OutCommand> outCommands_;
    double dt_;
};

#endif //JSB_SIMRUNNER_H
