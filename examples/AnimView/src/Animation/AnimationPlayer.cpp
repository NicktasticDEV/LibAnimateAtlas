#include "AnimationPlayer.h"
#include "AnimationAsset.h"
#include <GLFW/glfw3.h>

namespace AnimView {

AnimationPlayer::AnimationPlayer() {
    m_LastFrameTime = (float)glfwGetTime();
}

AnimationPlayer::~AnimationPlayer() = default;

void AnimationPlayer::Update() {
    if (m_State != PlaybackState::Playing || !m_CurrentAnimation) {
        m_LastFrameTime = (float)glfwGetTime();
        return;
    }

    float currentFrameTime = (float)glfwGetTime();
    float deltaTime = currentFrameTime - m_LastFrameTime;
    m_LastFrameTime = currentFrameTime;

    m_CurrentTime += deltaTime;
    
    // Loop animation
    float duration = GetDuration();
    if (duration > 0.0f && m_CurrentTime > duration) {
        m_CurrentTime = 0.0f;
    }
}

void AnimationPlayer::Play() {
    if (!m_CurrentAnimation) return;
    
    m_State = PlaybackState::Playing;
    m_LastFrameTime = (float)glfwGetTime();
}

void AnimationPlayer::Pause() {
    m_State = PlaybackState::Paused;
}

void AnimationPlayer::Stop() {
    m_State = PlaybackState::Stopped;
    m_CurrentTime = 0.0f;
}

void AnimationPlayer::SetTime(float time) {
    m_CurrentTime = time;
    if (m_CurrentTime < 0.0f) m_CurrentTime = 0.0f;
    
    float duration = GetDuration();
    if (duration > 0.0f && m_CurrentTime > duration) {
        m_CurrentTime = duration;
    }
}

bool AnimationPlayer::LoadAnimation(const std::string& path) {
    // TODO: Implement actual animation loading
    // For now, create a placeholder
    m_CurrentAnimation = std::make_shared<AnimationAsset>();
    m_CurrentAnimationName = path;
    m_CurrentTime = 0.0f;
    m_State = PlaybackState::Stopped;
    return true;
}

void AnimationPlayer::UnloadAnimation() {
    Stop();
    m_CurrentAnimation.reset();
    m_CurrentAnimationName.clear();
}

float AnimationPlayer::GetDuration() const {
    if (!m_CurrentAnimation) return 0.0f;
    return m_CurrentAnimation->GetDuration();
}

} // namespace AnimView
