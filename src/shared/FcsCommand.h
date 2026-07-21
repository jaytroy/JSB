//
// Created by jay on 6/27/26.
//

#ifndef JSB_FCSCOMMAND_H
#define JSB_FCSCOMMAND_H
#include <string>
#include <unordered_map>
#include <utility>

enum CommandType {
    Discrete, Continuous,
};

/**
 * Contains all possible FCS commands.
 * This is not the same as \ref FcsTarget.
 */
enum class FcsCommand {
    None,
    Pitch, Yaw, Roll, Throttle,

    Trim, TrimUp, TrimRight,

    //Single-trigger commands
    ThrottleUp, ThrottleDown,
    PitchUp, PitchDown,
    RollLeft, RollRight,
    YawLeft, YawRight,
    ToggleBrake,
    ToggleEngine,
};

namespace Command {
    /**
     * Maps strings to commands. Keybindings currently depend on this.
     * TODO: Make this dynamically rebindable.
     * This could also be in server, but I currently think it's better here.
     * @param req The string to be mapped into and FcsCommand;
     * @return The FcsCommand.
     */
    inline FcsCommand fromString(const std::string &req) {
        //This is currently a free function, it really shouldn't be
        static std::unordered_map<std::string, FcsCommand> registry = {
            {"none", FcsCommand::None},
            {"pitch", FcsCommand::Pitch},
            {"yaw", FcsCommand::Yaw},
            {"roll", FcsCommand::Roll},
            {"throttle", FcsCommand::Throttle},
            {"trim", FcsCommand::Trim},
            {"toggleEngine", FcsCommand::ToggleEngine}
        };

        auto out = registry.find(req);
        return out != registry.end() ? out->second : FcsCommand::None;
    }
}

struct OutCommand {
    FcsCommand command;
    CommandType type;
    double value = 0; //Value is optional
};
#endif //JSB_FCSCOMMAND_H
