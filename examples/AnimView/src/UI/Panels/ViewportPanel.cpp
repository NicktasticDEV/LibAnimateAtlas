#include "ViewportPanel.h"
#include <imgui.h>

namespace AnimView {

void ViewportPanel::OnImGuiRender() {
    if (!ImGui::Begin("Viewport", &m_IsOpen)) {
        ImGui::End();
        return;
    }

    ImVec2 viewportSize = ImGui::GetContentRegionAvail();
    
    // TODO: Render actual animation texture here
    // Example: ImGui::Image((void*)(intptr_t)textureID, viewportSize);

    ImGui::End();
}

} // namespace AnimView
