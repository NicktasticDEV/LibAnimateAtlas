#pragma once

#include <string>
#include <vector>
#include <memory>

#include "AnimateAtlas/Core/Display/DisplayObject.h"

namespace AnimateAtlas {
namespace Core {
namespace Timeline {

class Frame
{
public:
    Frame();
    ~Frame();

    std::vector<std::unique_ptr<Display::DisplayObject>> displayObjects;
    int index;
    int duration;
    std::string name;
    // Sound
    // Blend
};

} // namespace Timeline
} // namespace Core
} // namespace AnimateAtlas