#include "InspectorPanel.h"
#include <imgui.h>

namespace AnimView {

void InspectorPanel::OnImGuiRender() {
    if (!ImGui::Begin("Inspector", &m_IsOpen)) {
        ImGui::End();
        return;
    }
    
    ImGui::Text("Current Animation: %s", m_CurrentAnimation.c_str());
    ImGui::Text("Duration: %.2fs", m_Duration);
    
    ImGui::Separator();
    ImGui::Text("Properties:");
    
    // TODO: Display actual animation properties
    ImGui::BulletText("Frame Count: 30");
    ImGui::BulletText("FPS: 24");
    ImGui::BulletText("Layers: 5");
    ImGui::BulletText("Symbols: 8");

    ImGui::End();
}

} // namespace AnimView
