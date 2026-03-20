#pragma once

#include "AnimateAtlas/Core/Math/Matrix2D.h"

namespace AnimateAtlas {
namespace Core {
namespace Display {

class DisplayObject
{
public:
    Math::Matrix2D matrix;
    bool visible = true;

    DisplayObject() = default;
    virtual ~DisplayObject() = default;
};

} // namespace Display
} // namespace Core
} // namespace AnimateAtlas