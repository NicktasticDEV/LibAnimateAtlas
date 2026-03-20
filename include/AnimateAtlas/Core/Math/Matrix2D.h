#pragma once

namespace AnimateAtlas {
namespace Core {
namespace Math {

struct Matrix2D {
    float a = 1.0f;
    float b = 0.0f;
    float c = 0.0f;
    float d = 1.0f;
    float tx = 0.0f;
    float ty = 0.0f;

    Matrix2D() = default;
    Matrix2D(float a_, float b_, float c_, float d_, float tx_, float ty_)
        : a(a_), b(b_), c(c_), d(d_), tx(tx_), ty(ty_) {}

    static Matrix2D identity() { return {}; }
};

} // namespace Math
} // namespace Core
} // namespace AnimateAtlas
