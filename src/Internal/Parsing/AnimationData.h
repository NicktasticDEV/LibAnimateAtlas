#pragma once

#include <string>
#include <vector>
#include <nlohmann/json.hpp>

namespace AnimateAtlas {
namespace Internal {
namespace Parsing {

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
    AnimationSymbolInstanceData SYMBOL_Instance;
    AnimationAtlasInstanceData ATLAS_SPRITE_instance;
    AnimationTextFieldInstanceData textFIELD_Instance;
};

//TODO: struct TweenData
//TODO: struct SoundData

struct AnimationFrameData {
    int index;
    int duration;
    std::vector<AnimationElementData> elements;
    std::string Layer_name;
    //* Tween
    //* Sound
    //* Blend mode
};

struct AnimationLayerData {
    std::string Layer_name;
    std::string Layer_type;
    std::string Clipped_by;
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
    AnimationSymbolDictionaryData SYMBOL_DICTIONARY;
    AnimationMetaData metadata;
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

void from_json(const nlohmann::json& j, AnimationMatrixData& matrix);
void from_json(const nlohmann::json& j, AnimationMetaData& meta);

} // namespace Parsing
} // namespace Internal
} // namespace AnimateAtlas