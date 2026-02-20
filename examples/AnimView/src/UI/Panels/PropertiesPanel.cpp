#include "PropertiesPanel.h"
#include <imgui.h>

namespace AnimView {

void PropertiesPanel::OnImGuiRender() {
    if (!ImGui::Begin("Properties", &m_IsOpen)) {
        ImGui::End();
        return;
    }

    ImGui::Text("Type: %s", "Frame");

    ImGui::End();
}

} // namespace AnimView
