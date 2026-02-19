#pragma once

#include <string>
#include <memory>

namespace AnimView {

// Forward declaration
class AnimationAsset;

enum class PlaybackState {
    Stopped,
    Playing,
    Paused
};

class AnimationPlayer {
public:
    AnimationPlayer();
    ~AnimationPlayer();

    void Update();
    
    void Play();
    void Pause();
    void Stop();
    void SetTime(float time);
    
    bool LoadAnimation(const std::string& path);
    void UnloadAnimation();
    
    PlaybackState GetState() const { return m_State; }
    float GetCurrentTime() const { return m_CurrentTime; }
    float GetDuration() const;
    bool IsLoaded() const { return m_CurrentAnimation != nullptr; }
    const std::string& GetCurrentAnimationName() const { return m_CurrentAnimationName; }

private:
    std::shared_ptr<AnimationAsset> m_CurrentAnimation;
    std::string m_CurrentAnimationName;
    PlaybackState m_State = PlaybackState::Stopped;
    float m_CurrentTime = 0.0f;
    float m_LastFrameTime = 0.0f;
};

} // namespace AnimView
