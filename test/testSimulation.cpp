#include <catch2/catch_test_macros.hpp>

#include "simulation/Simulation.h"

// Constructing a Simulation loads the aircraft model from disk relative to
// $JSBGITDIR, so this is hidden behind the [.integration] tag and only runs when
// asked for explicitly: ./JSB_TEST "[integration]"
TEST_CASE("Simulation loads the c172p model", "[.integration][simulation]") {
    Simulation sim("c172p", "reset00.xml");
    REQUIRE(sim.getDt() > 0.0);
}
