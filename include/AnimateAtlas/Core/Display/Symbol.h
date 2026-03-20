#pragma once

#include <string>

#include "DisplayObject.h"

namespace AnimateAtlas {
namespace Core {
namespace Display {

class Symbol : public DisplayObject
{
public:
    // Timeline
    std::string name;
    int firstFrame;
    //? symbolType
    // Transformation Point
    // Loop type

    Symbol() = default;
    ~Symbol() override = default;
};

} // namespace Display
} // namespace Core
} // namespace AnimateAtlas