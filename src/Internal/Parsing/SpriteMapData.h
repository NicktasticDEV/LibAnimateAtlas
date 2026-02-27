#pragma once

#include <string>
#include <vector>
#include <nlohmann/json.hpp>

namespace AnimateAtlas {
namespace Internal {
namespace Parsing {

struct SpriteMapResolution { int w, h; };

struct SpriteMapSprite {
    std::string name;
    int x, y, w, h;
    bool rotated;
};

struct SpriteMapAtlas {
    std::vector<SpriteMapSprite> SPRITES;
};

struct SpriteMapMeta {
    std::string app, version, image, format, resolution;
    SpriteMapResolution size;
};

struct SpriteMapData {
    SpriteMapAtlas ATLAS;
    SpriteMapMeta meta;
};

void from_json(const nlohmann::json& j, SpriteMapResolution& res);
void from_json(const nlohmann::json& j, SpriteMapSprite& sprite);
void from_json(const nlohmann::json& j, SpriteMapAtlas& atlas);
void from_json(const nlohmann::json& j, SpriteMapMeta& meta);
void from_json(const nlohmann::json& j, SpriteMapData& data);

void to_json(nlohmann::json& j, const SpriteMapResolution& res);
void to_json(nlohmann::json& j, const SpriteMapSprite& sprite);
void to_json(nlohmann::json& j, const SpriteMapAtlas& atlas);
void to_json(nlohmann::json& j, const SpriteMapMeta& meta);
void to_json(nlohmann::json& j, const SpriteMapData& data);

} // namespace Parsing
} // namespace Internal
} // namespace AnimateAtlas