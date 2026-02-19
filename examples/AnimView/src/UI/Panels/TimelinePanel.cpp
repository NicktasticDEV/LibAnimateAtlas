#include "TimelinePanel.h"
#include <imgui.h>

namespace AnimView {

void TimelinePanel::OnImGuiRender() {
    if (!ImGui::Begin("Timeline", &m_IsOpen)) {
        ImGui::End();
        return;
    }
    
    // Playback controls
    if (ImGui::Button("Play")) {
        // TODO: Connect to AnimationPlayer
    }
    ImGui::SameLine();
    if (ImGui::Button("Pause")) {
        // TODO: Connect to AnimationPlayer
    }
    ImGui::SameLine();
    if (ImGui::Button("Stop")) {
        // TODO: Connect to AnimationPlayer
    }
    
    ImGui::Separator();
    
    // Timeline scrubber
    ImGui::Text("Time: %.2fs", m_TimelineScrubber);
    if (ImGui::SliderFloat("##Timeline", &m_TimelineScrubber, 0.0f, 1.5f, "%.2f")) {
        // TODO: Update animation time when scrubbing
    }
    
    ImGui::Separator();
    ImGui::Text("Frame: %d / 30", (int)(m_TimelineScrubber * 30.0f));

    ImGui::End();
}

} // namespace AnimView
