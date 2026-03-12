#pragma once

#include "Layer.h"

#include <string>
#include <vector>

namespace AnimateAtlas {
namespace Core {
namespace Timeline {

class Timeline
{
public:
    Timeline();
    ~Timeline();

    std::vector<Layer> layers;
    std::string name;
    int currentFrame;
    int frameCount;
};

} // namespace Timeline
} // namespace Core
} // namespace AnimateAtlas