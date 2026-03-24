#include "AnimateAtlas/Experimental/TestParse.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <nlohmann/json.hpp>

#include "AnimateAtlas/Core/Models/AnimationData.h"

using nlohmann::json;
using namespace AnimateAtlas::Core::Models;

namespace AnimateAtlas {
namespace Experimental {

void printAnimationData(AnimationTimelineData& timeline) {
    for (const auto& layer : timeline.LAYERS) {
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
            // Tween
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
                // Symbol Instance
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
                // Atlas Sprite Instance
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
}

void testParse(const char* path) {
    std::string animPath = std::string(path) + "/Animation.json";
    std::string metaPath = std::string(path) + "/metadata.json";

    std::ifstream animStream;
    std::ifstream metaStream;

    // For meta, Animate is Inline | BTA is as file
    bool checkMetaInline = false;

    // File
    std::cout << "- Opening files\n" << std::flush;
    animStream.open(animPath);
    metaStream.open(metaPath);

    if(!animStream) {
        std::cout << "- Animation file could not open\n" << std::flush;
        return;
    }
    if(!metaStream) {
        checkMetaInline = true;
    }

    // JSON parse
    std::stringstream animStringStream;
    animStringStream << animStream.rdbuf();
    json animJsonData = json::parse(animStringStream.str());
    AnimationRootData rootData = animJsonData.get<AnimationRootData>();
    
    if (!checkMetaInline) {
        std::stringstream metaStringStream;
        metaStringStream << metaStream.rdbuf();
        json metaJsonData = json::parse(metaStringStream.str());
        rootData.metadata = metaJsonData.get<AnimationMetaData>();
    }

    std::cout << "- Files parsed\n\n" << std::flush;

    // JSON read
    // Root animation data
    std::cout << "Animation Name: " << rootData.ANIMATION.name << std::endl;
    std::cout << "Animation SYMBOL Name: " << rootData.ANIMATION.SYMBOL_name << std::endl;

    std::cout << "---------" << std::endl;

    // Stage instance data
    std::cout << "Meta file version: " << rootData.metadata.value().version << std::endl;
    std::cout << "Meta name: " << rootData.metadata.value().name << std::endl;
    std::cout << "Meta BGColor: " << rootData.metadata.value().backgroundColor << std::endl;
    std::cout << "Meta width: " << rootData.metadata.value().width << std::endl;
    std::cout << "Meta height: " << rootData.metadata.value().height << std::endl;
    std::cout << "Meta ActionScript: " << rootData.metadata.value().asVersion << std::endl;
    std::cout << "Meta framerate: " << rootData.metadata.value().framerate << std::endl;

    std::cout << "---------" << std::endl;

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

    printAnimationData(rootData.ANIMATION.TIMELINE);

    if(rootData.SYMBOL_DICTIONARY.has_value()) {
        for (auto& symbol : rootData.SYMBOL_DICTIONARY.value().Symbols) {
            std::cout << std::endl;
            std::cout << "--------------------" << std::endl;
            std::cout << symbol.SYMBOL_name << " Symbol Timeline:" << std::endl;
            std::cout << "--------------------\n" << std::endl;

            printAnimationData(symbol.TIMELINE);
        }
    }

    std::cout << std::endl;

    animStream.close();
    metaStream.close();
}

} // namespace Experimental
} // namespace AnimateAtlas