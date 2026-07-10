//
// Created by jay on 7/10/26.
//

#include "Main.h"

#include "gfx/Window.h"
#include "SDL/EventPump.h"

int main(int argc, char** argv) {

    Window window_;
    EventPump pump_;

    inputHandler_.registerSinks(pump_);
    pump_.addSink(window_.getGfxSink());
    window_.renderFrame(rendererPayload); //This should be switched for a stream

    KeyboardSink keyboardSink_;
    window_.cleanup();
}
void registerSinks(EventPump& pump);
