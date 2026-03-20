#pragma once

#include <string>
#include <vector>

#include "Frame.h"

namespace AnimateAtlas {
namespace Core {
namespace Timeline {

class Layer
{
public:
    std::vector<Frame> frames;
    int frameCount;
    bool visible;
    std::string name;
    // Layertype
    // ParentLayer

    Layer();
    ~Layer();
};

} // namespace Timeline
} // namespace Core
} // namespace AnimateAtlas