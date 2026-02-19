#include "LibraryPanel.h"
#include <imgui.h>

namespace AnimView {

void LibraryPanel::OnImGuiRender() {
    if (!ImGui::Begin("Library", &m_IsOpen)) {
        ImGui::End();
        return;
    }

    //TODO: Empty space for now. Replace with actual preview of library element later
    ImGui::Dummy(ImVec2(0.0f, 150.0f));
    ImGui::Separator();
    
    // TODO: List available animations from asset directory
    if (ImGui::Selectable("SMLLOGOANIM (stage)", false)) {
        m_CurrentAnimation = "SMLLOGOANIM (Stage)";
    }
    if (ImGui::Selectable("SMLLogo", false)) {
        m_CurrentAnimation = "SMLLogo";
    }
    if (ImGui::Selectable("Symbol 1", false)) {
        m_CurrentAnimation = "Symbol 1";
    }
    if (ImGui::Selectable("Symbol 2", false)) {
        m_CurrentAnimation = "Symbol 2";
    }
    if (ImGui::Selectable("Symbol 3", false)) {
        m_CurrentAnimation = "Symbol 3";
    }


    ImGui::End();
}

} // namespace AnimView
