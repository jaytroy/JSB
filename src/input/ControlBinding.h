//
// Created by jay on 7/13/26.
//

#ifndef JSB_CONTROLBINDING_H
#define JSB_CONTROLBINDING_H
#include <vector>

#include "json.hpp"

struct Control {
    int index{};
    std::string name;
    NLOHMANN_DEFINE_TYPE_INTRUSIVE(Control, index, name);
};

/**
 * Data class that matches the input device JSON config exactly.
 * JSON gets loaded into this class when worked with.
 */
class ControlBinding {
public:
    std::string name{};
    int numAxes{};
    int numButtons{};
    int numHats{};
    std::vector<Control> axes{};
    std::vector<Control> buttons{};
    std::vector<Control> hats{};

    NLOHMANN_DEFINE_TYPE_INTRUSIVE(ControlBinding, name, numAxes, numButtons, numHats, axes, buttons, hats);
};

#endif //JSB_CONTROLBINDING_H
