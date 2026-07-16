//
// Created by jay on 6/28/26.
//

#ifndef JSB_FCSSTRATEGYFACTORY_H
#define JSB_FCSSTRATEGYFACTORY_H
#include <functional>
#include <memory>

#include "FcsStrategy.h"
#include "../../shared/FcsTarget.h"
#include "actions/Brake.hpp"
#include "actions/Engine.hpp"
#include "actions/Pitch.hpp"
#include "actions/Roll.hpp"
#include "actions/Throttle.hpp"
#include "actions/Yaw.hpp"

/**
 * Enables easy and decoupled creation of FCS commands.
 */
class FcsStrategyFactory {
public:
    using Creator = std::function<std::unique_ptr<FcsStrategy>()>;

    static std::unordered_map<FcsTarget, std::unique_ptr<FcsStrategy>> createAll() {
        static const std::unordered_map<FcsTarget, Creator> registry = {
            {FcsTarget::Throttle , [] { return std::make_unique<Throttle>();}},
            {FcsTarget::Pitch, [] {return std::make_unique<Pitch>(); }},
            {FcsTarget::Roll, [] {return std::make_unique<Roll>(); }},
            {FcsTarget::Brake, [] {return std::make_unique<Brake>(); }},
            {FcsTarget::Yaw, [] {return std::make_unique<Yaw>();}},
            {FcsTarget::Engine, [] {return std::make_unique<Engine>();}}
        };

        std::unordered_map<FcsTarget, std::unique_ptr<FcsStrategy>> result;
        for (auto& [name, creator] : registry) {
            result[name] = creator();
        }

        return result;
    }
};

#endif //JSB_FCSSTRATEGYFACTORY_H
