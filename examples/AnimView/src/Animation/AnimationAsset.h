#pragma once

#include <string>
#include <vector>

namespace AnimView {

// Placeholder for animation data
// You would integrate your actual animation library here
class AnimationAsset {
public:
    AnimationAsset() = default;
    ~AnimationAsset() = default;

    float GetDuration() const { return m_Duration; }
    void SetDuration(float duration) { m_Duration = duration; }
    
    const std::string& GetName() const { return m_Name; }
    void SetName(const std::string& name) { m_Name = name; }

private:
    std::string m_Name;
    float m_Duration = 1.5f; // Default placeholder duration
    
    // TODO: Add actual animation data structure
    // - Sprite sheets
    // - Keyframes
    // - Layers
    // - etc.
};

} // namespace AnimView
