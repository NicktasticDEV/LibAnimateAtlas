#pragma once

#include <glm/glm.hpp>

#include "AnimateAtlas/Core/Math/Matrix2D.h"

namespace AnimateAtlas {
namespace Interop {
namespace GLM {

inline glm::mat3 toMat3(const Core::Math::Matrix2D& m)
{
    // [ a  c  tx ]
    // [ b  d  ty ]
    // [ 0  0  1  ]
    return glm::mat3(
        glm::vec3(m.a, m.b, 0.0f),
        glm::vec3(m.c, m.d, 0.0f),
        glm::vec3(m.tx, m.ty, 1.0f));
}

inline Core::Math::Matrix2D fromMat3(const glm::mat3& m)
{
    return Core::Math::Matrix2D(
        m[0][0], // a
        m[0][1], // b
        m[1][0], // c
        m[1][1], // d
        m[2][0], // tx
        m[2][1]  // ty
    );
}

} // namespace GLM
} // namespace Interop
} // namespace AnimateAtlas
