include(FetchContent)
FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG v3.7.1
)
FetchContent_MakeAvailable(Catch2)

add_executable(JSB_TEST
        testInputHandler.cpp
        testSimulation.cpp
        testAircraft.cpp
)

target_link_libraries(JSB_TEST PRIVATE
        Catch2::Catch2WithMain
        JSB_CORE
)

include(Catch)
catch_discover_tests(JSB_TEST)
