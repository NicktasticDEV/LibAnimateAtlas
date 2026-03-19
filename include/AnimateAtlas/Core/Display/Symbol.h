#pragma once

#include <string>

#include "DisplayObject.h"

namespace AnimateAtlas {
namespace Core {
namespace Display {

class Symbol : public DisplayObject
{
public:
    Symbol();
    ~Symbol();

    // Timeline
    std::string name;
    int firstFrame;
    //? symbolType
    // Transformation Point
    // Loop type
};

} // namespace Display
} // namespace Core
} // namespace AnimateAtlas