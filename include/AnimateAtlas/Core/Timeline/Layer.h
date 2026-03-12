#pragma once

#include "Frame.h"

#include <string>
#include <vector>

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