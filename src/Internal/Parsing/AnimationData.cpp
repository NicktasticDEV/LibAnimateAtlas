#include "AnimationData.h"

#include "../JsonUtils.h"
#include <nlohmann/json.hpp>

namespace AnimateAtlas {
namespace Internal {
namespace Parsing {

void from_json(const nlohmann::json& j, AnimationMatrixData& matrix)
{
    //* Animate Atlas
    if (j.contains("Matrix3D") || j.contains("M3D")) {
        const auto& m3d = j.contains("Matrix3D") ? j["Matrix3D"] : j["M3D"];
        
        matrix.a = m3d.value("m00", 1.0f);
        matrix.b = m3d.value("m01", 0.0f);
        matrix.c = m3d.value("m10", 0.0f);
        matrix.d = m3d.value("m11", 1.0f);
        matrix.tx = m3d.value("m30", 0.0f);
        matrix.ty = m3d.value("m31", 0.0f);
    }
    //* BetterTextureAtlas
    else if (j.contains("Matrix") || j.contains("MX")) {
        const auto& mx = j.contains("Matrix") ? j["Matrix"] : j["MX"];
        
        matrix.a = mx[0].get<float>();
        matrix.b = mx[1].get<float>();
        matrix.c = mx[2].get<float>();
        matrix.d = mx[3].get<float>();
        matrix.tx = mx[4].get<float>();
        matrix.ty = mx[5].get<float>();
    }
    //* Default (identity matrix)
    else {
        matrix.a = 1.0f;
        matrix.b = 0.0f;
        matrix.c = 0.0f;
        matrix.d = 1.0f;
        matrix.tx = 0.0f;
        matrix.ty = 0.0f;
    }
}

void from_json(const nlohmann::json& j, AnimationMetaData& meta)
{
    read_json_key(j, {"version"}, meta.version);
    read_json_key(j, {"name"}, meta.name);
    read_json_key(j, {"backgroundColor"}, meta.backgroundColor);
    read_json_key(j, {"width"}, meta.width);
    read_json_key(j, {"height"}, meta.height);
    read_json_key(j, {"asVersion"}, meta.asVersion);
    read_json_key(j, {"framerate"}, meta.framerate);
}

} // namespace Parsing
} // namespace Internal
} // namespace AnimateAtlas