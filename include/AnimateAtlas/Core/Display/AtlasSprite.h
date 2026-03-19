#pragma once

#include "DisplayObject.h"
#include "AnimateAtlas/Core/Models/AnimationData.h"

using namespace AnimateAtlas::Core::Models;

namespace AnimateAtlas {
namespace Core {
namespace Display {

class AtlasSprite : public DisplayObject
{
public:
    AtlasSprite(AnimationAtlasInstanceData& data);
    ~AtlasSprite();
};

} // namespace Display
} // namespace Core
} // namespace AnimateAtlas