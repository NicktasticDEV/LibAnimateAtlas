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
    //std::ifstream metaStream;

    std::cout << "========================================" << std::endl;
    std::cout << "File Processing" << std::endl;
    std::cout << "========================================" << std::endl;

    // File
    std::cout << "- Opening files" << std::endl;
    animStream.open(animPath);
    //metaStream.open(metaPath);

    if(!animStream) {
        std::cout << "- Animation file could not open" << std::endl;
        return;
    }
    else {
        std::cout << "- Animation file opened" << std::endl;
    }

    /*
    if(!metaStream) {
        std::cout << "- Meta file could not open (Meta might be inside Animation file)" << std::endl;
    }
    else {
        std::cout << "- Meta file opened" << std::endl;
    }
    */

    // JSON parse
    std::stringstream animStringStream;
    animStringStream << animStream.rdbuf();
    //std::stringstream metaStringStream;
    //metaStringStream << metaStream.rdbuf();

    json jsonData = json::parse(animStringStream.str());
    AnimateAtlas::Internal::Parsing::AnimationRootData rootData = jsonData.get<AnimateAtlas::Internal::Parsing::AnimationRootData>();
    std::cout << "- JSON parsed" << std::endl;

    std::cout << "\n========================================" << std::endl;
    std::cout << "JSON Read" << std::endl;
    std::cout << "========================================" << std::endl;

    // JSON read
    std::cout << "Animation Name: " << rootData.ANIMATION.name << std::endl;
    std::cout << "Animation SYMBOL Name: " << rootData.ANIMATION.SYMBOL_name << std::endl;

    std::cout << std::endl;
}

} // namespace Data
} // namespace Core
} // namespace AnimateAtlas