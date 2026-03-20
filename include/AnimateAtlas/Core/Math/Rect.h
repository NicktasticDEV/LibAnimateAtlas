#pragma once

namespace AnimateAtlas {
namespace Core {
namespace Math {

struct Rect {
    float x = 0.0f;
    float y = 0.0f;
    float w = 0.0f;
    float h = 0.0f;

    bool empty() const { return w <= 0.0f || h <= 0.0f; }
};

} // namespace Math
} // namespace Core
} // namespace AnimateAtlas
