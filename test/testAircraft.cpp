#include <catch2/catch_test_macros.hpp>

#include "simulation/Aircraft.h"

// Aircraft holds a reference to a live FGFDMExec, so exercising it needs a
// loaded model the same way testSimulation.cpp does. Hidden behind
// [.integration] until there's a fixture for it.
TEST_CASE("Aircraft appends its state to the renderer payload", "[.integration][aircraft]") {
    JSBSim::FGFDMExec fdm;
    fdm.SetDebugLevel(0);

    Aircraft aircraft(fdm);

    std::vector<double> payload;
    aircraft.appendDataTo(payload);
    REQUIRE_FALSE(payload.empty());
}
