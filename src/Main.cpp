#include <thread>

#include "input/KeyboardSink.h"
#include "gfx/Window.h"
#include "model/Simulation.h"
#include "SDL/EventPump.h"

#define AIRCRAFT_MODEL "c172p"
#define RESET_FILE "reset00.xml"

/**
 * Welcome to this minimal JSB simulator. It's quite barebones right now, but it will keep getting bigger ;)
 * @return
 */
int main() {
    EventPump pump;
    KeyboardSink keyboardSink;
    Window window;
    pump.addSink(&keyboardSink);
    pump.addSink(window.getGfxSink());

    Simulation sim(AIRCRAFT_MODEL, RESET_FILE);
    const double dt = sim.getDt();

    while (pump.pump()) {
        std::vector<double> rendererPayload = sim.run(keyboardSink.drain());

        window.renderFrame(rendererPayload);

        std::this_thread::sleep_for(std::chrono::duration<double>(dt));
    }

    window.cleanup();
    std::cout << "Exited successfully" << std::endl;

    return 0;
}