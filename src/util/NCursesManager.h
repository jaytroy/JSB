//
// Created by jay on 6/26/26.
//

#ifndef JSB_CURSESMANAGER_H
#define JSB_CURSESMANAGER_H
#include "InputDevice.h"

/**
 * @brief The NCursesManager enables CLI input for the simulator.
 * This is very simple and basic, only enabling one key press to be read per tick.
 * In the future, it will be replaced with something more robust.
 */
class NCursesManager : public InputDevice {
public:
    NCursesManager();

    bool pollEvent(InputEvent &outEvent) override;
private:
    int c = -1;
};


#endif //JSB_CURSESMANAGER_H
