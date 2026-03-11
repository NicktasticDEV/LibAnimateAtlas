#include <initializer_list>
#include <optional>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

namespace AnimateAtlas {
namespace Internal {

template <typename T>
void read_json_key(const json& j, std::initializer_list<const char*> keys, T& destination) {
    for (const char* key : keys) {
        if (j.contains(key)) {
            j.at(key).get_to(destination);
            return;
        }
    }
}

template <typename T>
void read_json_key(const json& j, std::initializer_list<const char*> keys, std::optional<T>& destination) {
    for (const char* key : keys) {
        if (j.contains(key)) {
            destination = j.at(key).get<T>();
            return;
        }
    }
}

} // namespace Internal
} // namespace AnimateAtlas