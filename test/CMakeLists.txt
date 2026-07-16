add_executable(JSB_TEST
        testInputHandler.cpp
        testSimulation.cpp
        testAircraft.cpp
)

target_link_libraries(JSB_TEST PRIVATE
        Catch2::Catch2WithMain
        JSB_core
)

include(Catch)
catch_discover_tests(JSB_TEST)
