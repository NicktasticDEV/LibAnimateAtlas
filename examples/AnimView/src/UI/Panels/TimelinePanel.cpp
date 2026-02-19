#include "TimelinePanel.h"
#include <imgui.h>

namespace AnimView {

void TimelinePanel::OnImGuiRender() {
    if (!ImGui::Begin("Timeline", &m_IsOpen)) {
        ImGui::End();
        return;
    }
    
    // Timeline details
    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(25.0f, 10.0f));
    ImGui::BeginGroup();
        ImGui::Text("%0.2fFPS", (24.0f));
        ImGui::SameLine();
        ImGui::Text("%dF", (m_TimelineScrubber));
    ImGui::EndGroup();
    ImGui::PopStyleVar();

    // Playback controls
    ImGui::BeginGroup();
        if (ImGui::Button("Play")) {}
    ImGui::EndGroup();
    
    ImGui::Separator();
    
    // Timeline scrubber
    if (ImGui::SliderInt("##Timeline", &m_TimelineScrubber, 0.0f, 30.0f, "")) {}

    ImGui::End();
}

} // namespace AnimView
