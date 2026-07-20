#include <catch2/catch_test_macros.hpp>

#include "shared/AxisDevice.hpp"
#include "shared/FcsCommand.h"
#include "shared/FcsTarget.h"

TEST_CASE("targetOf maps every throttle command to the throttle system", "[fcs]") {
    REQUIRE(targetOf(FcsCommand::Throttle) == FcsTarget::Throttle);
    REQUIRE(targetOf(FcsCommand::ThrottleUp) == FcsTarget::Throttle);
    REQUIRE(targetOf(FcsCommand::ThrottleDown) == FcsTarget::Throttle);
}

TEST_CASE("targetOf maps axis commands to their system", "[fcs]") {
    REQUIRE(targetOf(FcsCommand::PitchUp) == FcsTarget::Pitch);
    REQUIRE(targetOf(FcsCommand::RollLeft) == FcsTarget::Roll);
    REQUIRE(targetOf(FcsCommand::YawRight) == FcsTarget::Yaw);
    REQUIRE(targetOf(FcsCommand::ToggleBrake) == FcsTarget::Brake);
    REQUIRE(targetOf(FcsCommand::ToggleEngine) == FcsTarget::Engine);
    REQUIRE(targetOf(FcsCommand::None) == FcsTarget::None);
}

TEST_CASE("fromString resolves known bindings and defaults to None", "[fcs]") {
    REQUIRE(fromString("pitch") == FcsCommand::Pitch);
    REQUIRE(fromString("throttle") == FcsCommand::Throttle);
    REQUIRE(fromString("not-a-command") == FcsCommand::None);
    REQUIRE(fromString("jhaskdjhakjshdka") == FcsCommand::None);
}

TEST_CASE("AxisDevice::normalize maps SDL axis range onto [-1, 1]", "[input]") {
    REQUIRE(AxisDevice::normalize(0.0,0) == 0.0);
    REQUIRE(AxisDevice::normalize(32767.0, 0) == 1.0);
    REQUIRE(AxisDevice::normalize(-32767.0, 0) == -1.0);
}

TEST_CASE("AxisDevice::normalize maps SDL axis range onto [0, 1]", "[input]") {
    REQUIRE(AxisDevice::normalize(32767.0, 1) == 1.0);
    REQUIRE(AxisDevice::normalize(-32767.0, 1) == 0.0);
}
