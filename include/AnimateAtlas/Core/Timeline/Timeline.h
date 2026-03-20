#pragma once

#include <string>
#include <vector>

#include "Layer.h"

namespace AnimateAtlas {
namespace Core {
namespace Timeline {

class Timeline
{
public:
    std::vector<Layer> layers;
    std::string name;
    int currentFrame;
    int frameCount;

    Timeline();
    ~Timeline();
};

} // namespace Timeline
} // namespace Core
} // namespace AnimateAtlas