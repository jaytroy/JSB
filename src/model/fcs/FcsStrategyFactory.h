//
// Created by jay on 6/28/26.
//

#ifndef JSB_FCSSTRATEGYFACTORY_H
#define JSB_FCSSTRATEGYFACTORY_H
#include <functional>
#include <memory>

#include "FcsStrategy.h"
#include "actions/Brake.h"
#include "actions/Engine.h"
#include "actions/Pitch.h"
#include "actions/Roll.h"
#include "actions/Throttle.h"
#include "actions/Yaw.h"

/**
 * Enables easy and decoupled creation of FCS commands.
 */
class FcsStrategyFactory {
public:
    using Creator = std::function<std::unique_ptr<FcsStrategy>()>;

    static std::unordered_map<std::string, std::unique_ptr<FcsStrategy>> createAll() {
        static const std::unordered_map<std::string, Creator> registry = {
            {"throttle", [] { return std::make_unique<Throttle>();}},
            {"pitch", [] {return std::make_unique<Pitch>(); }},
            {"roll", [] {return std::make_unique<Roll>(); }},
            {"brake", [] {return std::make_unique<Brake>(); }},
            {"yaw", [] {return std::make_unique<Yaw>();}},
            {"engine", [] {return std::make_unique<Engine>();}}
        };

        std::unordered_map<std::string, std::unique_ptr<FcsStrategy>> result;
        for (auto& [name, creator] : registry) {
            result[name] = creator();
        }

        return result;
    }
};

#endif //JSB_FCSSTRATEGYFACTORY_H
