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
    Layer();
    ~Layer();

    std::vector<Frame> frames;
    int frameCount;
    bool visible;
    std::string name;
    // Layertype
    // ParentLayer
};

} // namespace Timeline
} // namespace Core
} // namespace AnimateAtlas