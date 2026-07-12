//
// Created by jay on 7/12/26.
//

#ifndef JSB_SIMRUNNER_H
#define JSB_SIMRUNNER_H

#include <thread>

#include "gfx/Window.h"
#include "input/KeyboardSink.h"
#include "SDL/EventPump.h"
#include "simulation/Simulation.h"

/**
 * SimRunner is a proxy managing and running all parts of the simulator;
 */
class SimRunner {
public:
    SimRunner(const char* aircraftModel, const char* resetFile) : sim_(aircraftModel, resetFile) {
        pump_.addSink(&keyboardSink_);
        pump_.addSink(window_.getGfxSink());

        dt_ = sim_.getDt();
    }

    void run() {
        while (pump_.pump()) {
            std::vector<double> rendererPayload = sim_.run(keyboardSink_.drain());

            window_.renderFrame(rendererPayload);

            std::this_thread::sleep_for(std::chrono::duration<double>(dt_));
        }

        window_.cleanup();
        std::cout << "Exited successfully" << std::endl;
    }

    void updateSim() {
        //TODO make simm updateable
    }

private:
    Simulation sim_;
    EventPump pump_;
    KeyboardSink keyboardSink_;
    Window window_;
    double dt_;
};



#endif //JSB_SIMRUNNER_H
