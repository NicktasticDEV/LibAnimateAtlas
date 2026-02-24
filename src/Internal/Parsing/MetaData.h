#pragma once

#include <string>
#include <vector>
#include <nlohmann/json.hpp>

namespace AnimateAtlas {
namespace Internal {
namespace Parsing {

struct AnimationAtlasMetaData {
    std::string version;
    std::string name;
    std::string backgroundColor;
    int width;
    int height;
    int asVersion;
    double framerate;
};

void from_json(const nlohmann::json& j, AnimationAtlasMetaData& meta);

} // namespace Parsing
} // namespace Internal
} // namespace AnimateAtlas