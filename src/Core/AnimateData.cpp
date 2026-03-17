#include "AnimateAtlas/Core/Data/AnimateData.h"

#include "Internal/Parsing/AnimationData.h"

#include <nlohmann/json.hpp>

#include <iostream>
#include <fstream>
#include <sstream>

using nlohmann::json;

namespace AnimateAtlas {
namespace Core {
namespace Data {

void AnimateData::testParse(const char* path) {
    std::string animPath = std::string(path) + "/Animation.json";
    std::string metaPath = std::string(path) + "/metadata.json";

    std::ifstream animStream;

    std::cout << "========================================" << std::endl;
    std::cout << "File Processing" << std::endl;
    std::cout << "========================================" << std::endl;

    // File
    std::cout << "- Opening files" << std::endl;
    animStream.open(animPath);

    if(!animStream) {
        std::cout << "- Animation file could not open" << std::endl;
        return;
    }
    else {
        std::cout << "- Animation file opened" << std::endl;
    }

    // JSON parse
    std::stringstream animStringStream;
    animStringStream << animStream.rdbuf();

    json jsonData = json::parse(animStringStream.str());
    AnimateAtlas::Internal::Parsing::AnimationRootData rootData = jsonData.get<AnimateAtlas::Internal::Parsing::AnimationRootData>();
    std::cout << "- JSON parsed" << std::endl;

    std::cout << "\n========================================" << std::endl;
    std::cout << "JSON Read" << std::endl;
    std::cout << "========================================" << std::endl;

    // JSON read
    // Root animation data
    std::cout << "Animation Name: " << rootData.ANIMATION.name << std::endl;
    std::cout << "Animation SYMBOL Name: " << rootData.ANIMATION.SYMBOL_name << std::endl;

    std::cout << std::endl;

    // Stage instance data
    std::cout << "Stage Symbol Instance SYMBOL Name: " << rootData.ANIMATION.StageInstance.SYMBOL_Instance.SYMBOL_name << std::endl;
    std::cout << "Stage Symbol Instance first frame: " << rootData.ANIMATION.StageInstance.SYMBOL_Instance.firstFrame << std::endl;
    std::cout << "Stage Symbol Instance symbol type: " << rootData.ANIMATION.StageInstance.SYMBOL_Instance.symbolType << std::endl;
    std::cout << "Stage Symbol Instance loop: " << rootData.ANIMATION.StageInstance.SYMBOL_Instance.loop << std::endl;
    std::cout << "Stage Symbol Instance transformation point: (" << rootData.ANIMATION.StageInstance.SYMBOL_Instance.transformationPoint.x << ", " << rootData.ANIMATION.StageInstance.SYMBOL_Instance.transformationPoint.y << ")" << std::endl;
    std::cout << "Stage Symbol Instance matrix: (" << rootData.ANIMATION.StageInstance.SYMBOL_Instance.Matrix.a << ", " << rootData.ANIMATION.StageInstance.SYMBOL_Instance.Matrix.b << ", " << rootData.ANIMATION.StageInstance.SYMBOL_Instance.Matrix.c << ", " << rootData.ANIMATION.StageInstance.SYMBOL_Instance.Matrix.d << ", " << rootData.ANIMATION.StageInstance.SYMBOL_Instance.Matrix.tx << ", " << rootData.ANIMATION.StageInstance.SYMBOL_Instance.Matrix.ty << ")" << std::endl;

    std::cout << std::endl;

    std::cout << "--------------------" << std::endl;
    std::cout << rootData.ANIMATION.StageInstance.SYMBOL_Instance.SYMBOL_name << " Root Timeline:" << std::endl;
    std::cout << "--------------------\n" << std::endl;
    for (const auto& layer : rootData.ANIMATION.TIMELINE.LAYERS) {
        // Layers
        std::cout << "Layer Name: " << layer.Layer_name << std::endl;
        std::cout << "Layer Type: " << layer.Layer_type.value_or("") << std::endl;
        std::cout << "Clipped By: " << layer.Clipped_by.value_or("") << std::endl;
        std::cout << "| " << std::endl;

        // Frames
        for (const auto& frame : layer.Frames) {
            std::cout << "| Frame Index: " << frame.index << std::endl;
            std::cout << "| Frame Duration: " << frame.duration << std::endl;
            std::cout << "| Frame Name: " << frame.name.value_or("") << std::endl;
            if (frame.tween.has_value()) {
                const auto& tween = frame.tween.value();
                std::cout << "| Tween Data:" << std::endl;
                std::cout << "| | Tween Type: " << tween.type << std::endl;
                std::cout << "| | Tween Rotate: " << tween.rotate << std::endl;
                std::cout << "| | Tween Rotate Times: " << tween.rotateTimes << std::endl;
                std::cout << "| | Tween Scale: " << std::boolalpha << tween.scale << std::noboolalpha << std::endl;
                std::cout << "| | Tween Snap: " << std::boolalpha << tween.snap << std::noboolalpha << std::endl;
                std::cout << "| | Tween Sync: " << std::boolalpha << tween.sync << std::noboolalpha << std::endl;
                std::cout << "| | Tween Curves: " << std::endl;

                // Tween Curves
                for (const auto& curve : tween.curves) {
                    std::cout << "| | | (" << curve.x << ", " << curve.y << ")" << std::endl;
                }
            }
            
            // Frame elements
            if (!frame.elements.empty())
            {
                std::cout << "| Elements: " << std::endl;
            }
            for (const auto& element : frame.elements) {
                if (element.SYMBOL_Instance.has_value()) {
                    const auto& si = element.SYMBOL_Instance.value();
                    std::cout << "| | Element Symbol Instance SYMBOL Name: " << si.SYMBOL_name << std::endl;
                    std::cout << "| | Element Symbol Instance first frame: " << si.firstFrame << std::endl;
                    std::cout << "| | Element Symbol Instance symbol type: " << si.symbolType << std::endl;
                    std::cout << "| | Element Symbol Instance loop: " << si.loop << std::endl;
                    std::cout << "| | Element Symbol Instance transformation point: (" << si.transformationPoint.x << ", " << si.transformationPoint.y << ")" << std::endl;
                    std::cout << "| | Element Symbol Instance matrix: (" << si.Matrix.a << ", " << si.Matrix.b << ", " << si.Matrix.c << ", " << si.Matrix.d << ", " << si.Matrix.tx << ", " << si.Matrix.ty << ")" << std::endl;
                    std::cout << "| | "<< std::endl;
                }
                if (element.ATLAS_SPRITE_instance.has_value()) {
                    const auto& asi = element.ATLAS_SPRITE_instance.value();
                    std::cout << "| | Element Atlas Sprite Instance Name: " << asi.name << std::endl;
                    std::cout << "| | Element Atlas Sprite Instance matrix: (" << asi.Matrix.a << ", " << asi.Matrix.b << ", " << asi.Matrix.c << ", " << asi.Matrix.d << ", " << asi.Matrix.tx << ", " << asi.Matrix.ty << ")" << std::endl;
                    std::cout << "| | "<< std::endl;
                }
            }

            std::cout << "|" << std::endl;
        }
    }



    std::cout << std::endl;
}

} // namespace Data
} // namespace Core
} // namespace AnimateAtlas