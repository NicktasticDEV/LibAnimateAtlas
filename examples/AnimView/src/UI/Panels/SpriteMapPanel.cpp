#include "SpriteMapPanel.h"
#include <imgui.h>

namespace AnimView {

void SpriteMapPanel::OnImGuiRender() {
    if (!ImGui::Begin("Sprite Map", &m_IsOpen)) {
        ImGui::End();
        return;
    }

    //TODO: Viewport that renders the SpriteMap and displays details on the sprites and stuff

    ImGui::End();
}

} // namespace AnimView
