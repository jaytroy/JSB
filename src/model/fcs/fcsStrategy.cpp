//
// Created by jay on 6/26/26.
//

#include "fcsStrategy.h"

#include <stdexcept>

constexpr std::string_view to_string(ControlChannel c) {
    switch (c) {
        case ControlChannel::Elevator: return FCS::elevator;
        case ControlChannel::Aileron: return FCS::aileron;
        case ControlChannel::Rudder: return FCS::rudder;
        case ControlChannel::Throttle: return FCS::throttle;
    }
    throw std::runtime_error("Unknown FCS channel used");
}
