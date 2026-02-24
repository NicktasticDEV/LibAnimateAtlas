#pragma once

#include <string>
#include <vector>
#include <nlohmann/json.hpp>

namespace AnimateAtlas {
namespace Internal {
namespace Parsing {

struct AnimationTransformationPointData {
    double x;
    double y;
};

//TODO:
struct AnimationMatrixData {
    //* Different for regular and better versions
    // Regular has 16 floats and better has 6 floats
};

struct AnimationMetaData {
    std::string version;
    std::string name;
    std::string backgroundColor;
    int width;
    int height;
    int asVersion;
    double framerate;
};

struct AnimationColorData {
    std::string mode;
    double redMultiplier;
    double greenMultiplier;
    double blueMultiplier;
    double alphaMultiplier;

    double redOffset;
    double greenOffset;
    double blueOffset;
    double alphaOffset;

    std::string tintColor;
    double tintMultiplier;
    double brightness;
};

struct AnimationGradientData {
    double ratio;
    std::string color;
    double alpha;
};

//TODO: struct FilterData
struct AnimationFilterData {

};

struct AnimationSymbolInstanceData {
    std::string SYMBOL_name;
    int firstFrame;
    std::string symbolType;
    AnimationTransformationPointData transformationPoint;
    std::string loop;
    std::vector<int> Matrix; //TODO: Replace with AnimationMatrixData
    // Blend
    // Color
    // Filter
};

struct AnimationAtlasInstanceData {
    std::string name;
    // AnimationMatrixData
};

struct AnimationTextFieldInstanceData {
    // AnimationMatrixData
    // Text
    // Type
    // Instance name
    // Orientation
    // Line Type
    // AnimationTextFieldAttributesData
    // Border
    // Sharpness
    // Thickness
    // Max characters
};

struct AnimationElementData {
    //  - SymbolInstanceData
    //  - AtlasInstanceData
    //  - TextFieldInstanceData
};

//TODO: struct TweenData
//TODO: struct SoundData

struct AnimationFrameData {
    int index;
    int duration;
    std::vector<AnimationElementData> elements;
    std::string Layer_name;
    // Tween
    // Sound
    // Blend mode
};

struct AnimationLayerData {
    std::string Layer_name;
    // Layer type
    // Clipped by
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
    AnimationSymbolInstanceData SYMBOL_Instance; //? Should this be vector (probably note since it seems like their is ever only one symbol)
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
    // Metadata
};

//TODO: 
struct AnimationTextFieldAttributesData {
    /*
        offset
        length
        alias
        align
        autoKern
        bold
        italic
        charPosition
        charSpacing
        lineSpacing
        font
        Size
        color
        indent
        leftMargin
        rightMargin
        URL
    */
};

/*
    OTHER KNOWN DATA
    - ActionScript
*/

void from_json(const nlohmann::json& j, AnimationMetaData& meta);

} // namespace Parsing
} // namespace Internal
} // namespace AnimateAtlas