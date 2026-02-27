#include "SpriteMapData.h"

#include "../JsonUtils.h"
#include <nlohmann/json.hpp>

namespace AnimateAtlas {
namespace Internal {
namespace Parsing {

// ============================================================
// From JSON functions
// ============================================================
void from_json(const nlohmann::json& j, SpriteMapResolution& res)
{
    read_json_key(j, {"w"}, res.w);
    read_json_key(j, {"h"}, res.h);
}

void from_json(const nlohmann::json& j, SpriteMapSprite& sprite)
{
    read_json_key(j, {"name"}, sprite.name);
    read_json_key(j, {"x"}, sprite.x);
    read_json_key(j, {"y"}, sprite.y);
    read_json_key(j, {"w"}, sprite.w);
    read_json_key(j, {"h"}, sprite.h);
    read_json_key(j, {"rotated"}, sprite.rotated);
}

void from_json(const nlohmann::json& j, SpriteMapAtlas& atlas)
{
    read_json_key(j, {"SPRITES"}, atlas.SPRITES);
}

void from_json(const nlohmann::json& j, SpriteMapMeta& meta)
{
    read_json_key(j, {"app"}, meta.app);
    read_json_key(j, {"version"}, meta.version);
    read_json_key(j, {"image"}, meta.image);
    read_json_key(j, {"format"}, meta.format);
    read_json_key(j, {"size"}, meta.size);
    read_json_key(j, {"resolution"}, meta.resolution);
}

void from_json(const nlohmann::json& j, SpriteMapData& data)
{
    read_json_key(j, {"ATLAS"}, data.ATLAS);
    read_json_key(j, {"meta"}, data.meta);
}

// ============================================================
// To JSON functions
// ============================================================
void to_json(nlohmann::json& j, const SpriteMapResolution& res)
{
    j = nlohmann::json{
        {"w", res.w},
        {"h", res.h}
    };
}

void to_json(nlohmann::json& j, const SpriteMapSprite& sprite)
{
    j = nlohmann::json{
        {"name", sprite.name},
        {"x", sprite.x},
        {"y", sprite.y},
        {"w", sprite.w},
        {"h", sprite.h},
        {"rotated", sprite.rotated}
    };
}

void to_json(nlohmann::json& j, const SpriteMapAtlas& atlas)
{
    j = nlohmann::json{
        {"SPRITES", atlas.SPRITES}
    };
}

void to_json(nlohmann::json& j, const SpriteMapMeta& meta)
{
    j = nlohmann::json{
        {"app", meta.app},
        {"version", meta.version},
        {"image", meta.image},
        {"format", meta.format},
        {"size", meta.size},
        {"resolution", meta.resolution}
    };
}

void to_json(nlohmann::json& j, const SpriteMapData& data)
{
    j = nlohmann::json{
        {"ATLAS", data.ATLAS},
        {"meta", data.meta}
    };
}

} // namespace Parsing
} // namespace Internal
} // namespace AnimateAtlas