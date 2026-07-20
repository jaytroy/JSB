//
// Created by jay on 7/20/26.
//

#ifndef JSB_RENDERERPAYLOAD_HPP
#define JSB_RENDERERPAYLOAD_HPP

#include "../external/json.hpp"

/**
 * Contains data to be sent to the renderer.
 */
struct RendererPayload {
    double time = 0.0;
    double north = 0.0;
    double east = 0.0;
    double up = 0.0;
    double heading = 0.0;
    double airspeed = 0.0;
    double throttle = 0.0;
    double rpm = 0.0;
    double pitch = 0.0;
    double roll = 0.0;
    double brake = 0.0;

    NLOHMANN_DEFINE_TYPE_INTRUSIVE(RendererPayload, time, north, east, up,
        heading, airspeed, throttle, rpm, pitch, roll, brake)
};

#endif //JSB_RENDERERPAYLOAD_HPP
