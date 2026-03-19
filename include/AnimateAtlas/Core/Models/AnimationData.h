#pragma once

#include <optional>
#include <string>
#include <vector>
#include <nlohmann/json.hpp>

namespace AnimateAtlas {
namespace Core {
namespace Models {

struct AnimationTransformationPointData {
    float x;
    float y;
};

struct AnimationMatrixData {
    float a, b, c, d, tx, ty;
};

struct AnimationMetaData {
    std::string version;
    std::string name;
    std::string backgroundColor;
    int width;
    int height;
    int asVersion;
    float framerate;
};

struct AnimationColorData {
    std::string mode;
    float redMultiplier;
    float greenMultiplier;
    float blueMultiplier;
    float alphaMultiplier;

    float redOffset;
    float greenOffset;
    float blueOffset;
    float alphaOffset;

    std::string tintColor;
    float tintMultiplier;
    float brightness;
};

struct AnimationGradientData {
    float ratio;
    std::string color;
    float alpha;
};

struct AnimationFilterData {
    std::string name;
    float blurX;
    float blurY;
    int quality;
    int brightness;
    int hue;
    int contrast;
    int saturation;
    float distance;
    bool knockout;
    std::string type;
    float strength;
    float angle;
    float alpha;
    float shadowAlpha;
    std::string highlightColor;
    std::string shadowColor;
    bool inner;
    bool hideObject;
    std::string color;
    std::vector<AnimationGradientData> gradientEntries;
};

struct AnimationSymbolInstanceData {
    std::string SYMBOL_name;
    int firstFrame;
    std::string symbolType;
    AnimationTransformationPointData transformationPoint;
    std::string loop;
    AnimationMatrixData Matrix;
    //* Blend
    AnimationColorData color;
    std::vector<AnimationFilterData> filters;
};

struct AnimationAtlasInstanceData {
    std::string name;
    AnimationMatrixData Matrix;
};

//TODO: 
struct AnimationTextFieldAttributesData {
    /*
        * offset
        * length
        * alias
        * align
        * autoKern
        * bold
        * italic
        * charPosition
        * charSpacing
        * lineSpacing
        * font
        * Size
        * color
        * indent
        * leftMargin
        * rightMargin
        * URL
    */
};

//TODO: 
struct AnimationTextFieldInstanceData {
    //* AnimationMatrixData
    //* Text
    //* Type
    //* Instance name
    //* Orientation
    //* Line Type
    //* AnimationTextFieldAttributesData
    //* Border
    //* Sharpness
    //* Thickness
    //* Max characters
};

struct AnimationElementData {
    std::optional<AnimationSymbolInstanceData> SYMBOL_Instance;
    std::optional<AnimationAtlasInstanceData> ATLAS_SPRITE_instance;
    std::optional<AnimationTextFieldInstanceData> textFIELD_Instance;
};

struct AnimationCurveData {
    float x;
    float y;
};

struct AnimationTweenData {
    std::vector<AnimationCurveData> curves;
    std::string type;
    std::string rotate;
    int rotateTimes;
    bool scale;
    bool snap;
    bool sync;
};

//TODO: struct SoundData

struct AnimationFrameData {
    int index;
    int duration;
    std::vector<AnimationElementData> elements;
    std::optional<std::string> name;
    std::optional<AnimationTweenData> tween;
    //* Sound
    //* Blend mode
};

struct AnimationLayerData {
    std::string Layer_name;
    std::optional<std::string> Layer_type;
    std::optional<std::string> Clipped_by;
    std::vector<AnimationFrameData> Frames;
};

struct AnimationTimelineData {
    std::vector<AnimationLayerData> LAYERS;
};

struct AnimationSymbolDictionaryEntryData {
    std::string SYMBOL_name;
    AnimationTimelineData TIMELINE;
};

struct AnimationSymbolDictionaryData {
    std::vector<AnimationSymbolDictionaryEntryData> Symbols;
};

struct AnimationStageInstanceData {
    AnimationSymbolInstanceData SYMBOL_Instance; //? Should this be vector (probably not since it seems like their is ever only one symbol)
};

struct AnimationData {
    std::string name;
    AnimationStageInstanceData StageInstance;
    std::string SYMBOL_name;
    AnimationTimelineData TIMELINE;
};

struct AnimationRootData {
    AnimationData ANIMATION;
    std::optional<AnimationSymbolDictionaryData> SYMBOL_DICTIONARY;
    std::optional<AnimationMetaData> metadata;
};

void from_json(const nlohmann::json& j, AnimationTransformationPointData& point);
void from_json(const nlohmann::json& j, AnimationMatrixData& matrix);
void from_json(const nlohmann::json& j, AnimationMetaData& meta);
void from_json(const nlohmann::json& j, AnimationColorData& color);
void from_json(const nlohmann::json& j, AnimationGradientData& gradient);
void from_json(const nlohmann::json& j, AnimationFilterData& filter);
void from_json(const nlohmann::json& j, AnimationSymbolInstanceData& symbolInstance);
void from_json(const nlohmann::json& j, AnimationAtlasInstanceData& atlasInstance);
void from_json(const nlohmann::json& j, AnimationTextFieldAttributesData& textFieldAttributes);
void from_json(const nlohmann::json& j, AnimationTextFieldInstanceData& textFieldInstance);
void from_json(const nlohmann::json& j, AnimationElementData& element);
void from_json(const nlohmann::json& j, AnimationCurveData& curve);
void from_json(const nlohmann::json& j, AnimationTweenData& tween);
void from_json(const nlohmann::json& j, AnimationFrameData& frame);
void from_json(const nlohmann::json& j, AnimationLayerData& layer);
void from_json(const nlohmann::json& j, AnimationTimelineData& timeline);
void from_json(const nlohmann::json& j, AnimationSymbolDictionaryEntryData& symbolDictionaryEntry);
void from_json(const nlohmann::json& j, AnimationSymbolDictionaryData& symbolDictionary);
void from_json(const nlohmann::json& j, AnimationStageInstanceData& stageInstance);
void from_json(const nlohmann::json& j, AnimationData& animation);
void from_json(const nlohmann::json& j, AnimationRootData& root);

void to_json(nlohmann::json& j, const AnimationTransformationPointData& point);
void to_json(nlohmann::json& j, const AnimationMatrixData& matrix);
void to_json(nlohmann::json& j, const AnimationMetaData& meta);
void to_json(nlohmann::json& j, const AnimationColorData& color);
void to_json(nlohmann::json& j, const AnimationGradientData& gradient);
void to_json(nlohmann::json& j, const AnimationFilterData& filter);
void to_json(nlohmann::json& j, const AnimationSymbolInstanceData& symbolInstance);
void to_json(nlohmann::json& j, const AnimationAtlasInstanceData& atlasInstance);
void to_json(nlohmann::json& j, const AnimationTextFieldAttributesData& textFieldAttributes);
void to_json(nlohmann::json& j, const AnimationTextFieldInstanceData& textFieldInstance);
void to_json(nlohmann::json& j, const AnimationElementData& element);
void to_json(nlohmann::json& j, const AnimationCurveData& curve);
void to_json(nlohmann::json& j, const AnimationTweenData& tween);
void to_json(nlohmann::json& j, const AnimationFrameData& frame);
void to_json(nlohmann::json& j, const AnimationLayerData& layer);
void to_json(nlohmann::json& j, const AnimationTimelineData& timeline);
void to_json(nlohmann::json& j, const AnimationSymbolDictionaryEntryData& symbolDictionaryEntry);
void to_json(nlohmann::json& j, const AnimationSymbolDictionaryData& symbolDictionary);
void to_json(nlohmann::json& j, const AnimationStageInstanceData& stageInstance);
void to_json(nlohmann::json& j, const AnimationData& animation);
void to_json(nlohmann::json& j, const AnimationRootData& root);

} // namespace Models
} // namespace Core
} // namespace AnimateAtlas