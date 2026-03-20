#pragma once

#include "DisplayObject.h"

#include "AnimateAtlas/Core/Models/AnimationData.h"
#include "AnimateAtlas/Core/Math/Rect.h"

using namespace AnimateAtlas::Core::Models;
using namespace AnimateAtlas::Core::Math;

namespace AnimateAtlas {
namespace Core {
namespace Display {

class AtlasSprite : public DisplayObject
{
public:
    Rect frame{};

    AtlasSprite() = default;
    AtlasSprite(AnimationAtlasInstanceData data);

    ~AtlasSprite() override = default;
};

} // namespace Display
} // namespace Core
} // namespace AnimateAtlas