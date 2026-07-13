//
// Created by jay on 7/13/26.
//

#ifndef JSB_INPUTDEVICEFACTORY_H
#define JSB_INPUTDEVICEFACTORY_H
#include <functional>
#include <memory>

#include "AxisDevice.h"


class InputDeviceFactory {
public:
    using Creator = std::function<std::unique_ptr<AxisDevice>()>;

};


#endif //JSB_INPUTDEVICEFACTORY_H
