#include "AnimationData.h"

#include "../JsonUtils.h"
#include <nlohmann/json.hpp>

namespace AnimateAtlas {
namespace Internal {
namespace Parsing {

// ============================================================
// From JSON functions
// ============================================================
void from_json(const nlohmann::json& j, AnimationTransformationPointData& point)
{
    read_json_key(j, {"x"}, point.x);
    read_json_key(j, {"y"}, point.y);
}

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
    read_json_key(j, {"V", "version",}, meta.version);
    read_json_key(j, {"name"}, meta.name);
    read_json_key(j, {"BGC", "backgroundColor"}, meta.backgroundColor);
    read_json_key(j, {"W", "width"}, meta.width);
    read_json_key(j, {"H", "height"}, meta.height);
    read_json_key(j, {"asVersion"}, meta.asVersion);
    read_json_key(j, {"FRT", "framerate"}, meta.framerate);
}

void from_json(const nlohmann::json& j, AnimationColorData& color)
{
    read_json_key(j, {"M", "mode"}, color.mode);
    read_json_key(j, {"RM", "redMultiplier"}, color.redMultiplier);
    read_json_key(j, {"GM", "greenMultiplier"}, color.greenMultiplier);
    read_json_key(j, {"BM", "blueMultiplier"}, color.blueMultiplier);
    read_json_key(j, {"AM", "alphaMultiplier"}, color.alphaMultiplier);
    read_json_key(j, {"RO", "redOffset"}, color.redOffset);
    read_json_key(j, {"GO", "greenOffset"}, color.greenOffset);
    read_json_key(j, {"BO", "blueOffset"}, color.blueOffset);
    read_json_key(j, {"AO", "alphaOffset"}, color.alphaOffset);
    read_json_key(j, {"TC", "tintColor"}, color.tintColor);
    read_json_key(j, {"TM", "tintMultiplier"}, color.tintMultiplier);
    read_json_key(j, {"BRT", "brightness"}, color.brightness);
}

void from_json(const nlohmann::json& j, AnimationGradientData& gradient)
{
    read_json_key(j, {"R", "ratio"}, gradient.ratio);
    read_json_key(j, {"C", "color"}, gradient.color);
    read_json_key(j, {"A", "alpha"}, gradient.alpha);
}

//TODO: AnimationFilterData

void from_json(const nlohmann::json& j, AnimationSymbolInstanceData& instance)
{
    read_json_key(j, {"SN", "SYMBOL_name"}, instance.SYMBOL_name);
    read_json_key(j, {"FF", "firstFrame"}, instance.firstFrame);
    read_json_key(j, {"ST", "symbolType"}, instance.symbolType);
    read_json_key(j, {"TRP", "transformationPoint"}, instance.transformationPoint);
    read_json_key(j, {"LP", "loop"}, instance.loop);
    // MATRIX
    // BLEND
    read_json_key(j, {"C", "color"}, instance.color);
    read_json_key(j, {"F", "filters"}, instance.filters);
}

void from_json(const nlohmann::json& j, AnimationAtlasInstanceData& instance)
{
    read_json_key(j, {"N", "name"}, instance.name);
    // MATRIX
}

void from_json(const nlohmann::json& j, AnimationElementData& element)
{
    read_json_key(j, {"SI", "SYMBOL_Instance"}, element.SYMBOL_Instance);
    read_json_key(j, {"ASI", "ATLAS_SPRITE_instance"}, element.ATLAS_SPRITE_instance);
    read_json_key(j, {"TFI", "textFIELD_Instance"}, element.textFIELD_Instance);
}

void from_json(const nlohmann::json& j, AnimationCurveData& curve)
{
    read_json_key(j, {"X"}, curve.x);
    read_json_key(j, {"Y"}, curve.y);
}

//? Check keys
void from_json(const nlohmann::json& j, AnimationTweenData& tween)
{
    read_json_key(j, {"C", "curves"}, tween.curves);
    read_json_key(j, {"T", "type"}, tween.type);
    read_json_key(j, {"R", "rotate"}, tween.rotate);
    read_json_key(j, {"RT", "rotateTimes"}, tween.rotateTimes);
    read_json_key(j, {"S", "scale"}, tween.scale);
    read_json_key(j, {"SN", "snap"}, tween.snap);
    read_json_key(j, {"SY", "sync"}, tween.sync);
}

void from_json(const nlohmann::json& j, AnimationFrameData& frame)
{
    read_json_key(j, {"I", "index"}, frame.index);
    read_json_key(j, {"DU", "duration"}, frame.duration);
    read_json_key(j, {"E", "elements"}, frame.elements);
    read_json_key(j, {"N", "name"}, frame.Layer_name);
    read_json_key(j, {"T", "tween"}, frame.tween);
    // SOUND
    // BLEND
}


} // namespace Parsing
} // namespace Internal
} // namespace AnimateAtlas