#include <catch2/catch_test_macros.hpp>

#include "simulation/Simulation.h"

// Constructing a Simulation loads the aircraft model from disk relative to
// $JSBGITDIR, so this is hidden behind the [.integration] tag and only runs when
// asked for explicitly: ./JSB_TEST "[integration]"
TEST_CASE("Simulation loads the c172p model", "[.integration][simulation]") {
    Simulation sim("c172p", "reset00.xml");
    REQUIRE(sim.getDt() > 0.0);
}

TEST_CASE("Simulation constructor throws when JSBGITDIR is not set", "[simulation]") {
    unsetenv("JSBGITDIR");
    REQUIRE_THROWS(Simulation("c172p", "reset00.xml"));
}

TEST_CASE("Simulation constructor throws when no resetFile is provided", "[simulation]") {
    REQUIRE_THROWS(Simulation("c172p", ""));
}

TEST_CASE("Simulation constructor throws when no aircraftModel is provided", "[simulation]") {
    REQUIRE_THROWS(Simulation("", "reset00.xml"));
}
