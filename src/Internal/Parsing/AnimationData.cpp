#include "AnimationData.h"

#include "../JsonUtils.h"
#include <nlohmann/json.hpp>

namespace AnimateAtlas {
namespace Internal {
namespace Parsing {

void from_json(const nlohmann::json& j, AnimationMetaData& meta)
{
    read_json_key(j, {"version"}, meta.version);
    read_json_key(j, {"name"}, meta.name);
    read_json_key(j, {"backgroundColor"}, meta.backgroundColor);
    read_json_key(j, {"width"}, meta.width);
    read_json_key(j, {"height"}, meta.height);
    read_json_key(j, {"asVersion"}, meta.asVersion);
    read_json_key(j, {"framerate"}, meta.framerate);
}

} // namespace Parsing
} // namespace Internal
} // namespace AnimateAtlas