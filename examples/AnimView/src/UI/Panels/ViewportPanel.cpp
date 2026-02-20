#include "ViewportPanel.h"

#include <imgui.h>
#include <glad/glad.h>

namespace AnimView {

ViewportPanel::ViewportPanel()
{
    // Create an initial framebuffer; it will be resized on the first frame
    m_Framebuffer = std::make_unique<Framebuffer>(1, 1);
}

void ViewportPanel::OnImGuiRender()
{
    // Remove padding so the image fills the full panel area
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
    if (!ImGui::Begin("Viewport", &m_IsOpen))
    {
        ImGui::PopStyleVar();
        ImGui::End();
        return;
    }
    ImGui::PopStyleVar();

    ImVec2 viewportSize = ImGui::GetContentRegionAvail();
    int vpW = (int)viewportSize.x;
    int vpH = (int)viewportSize.y;

    if (vpW > 0 && vpH > 0)
    {
        // Resize the FBO if the panel size changed
        m_Framebuffer->Resize(vpW, vpH);

        // --- Render your scene into the FBO ---
        m_Framebuffer->Bind();

        glClearColor(0.15f, 0.15f, 0.15f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // TODO: Draw your animation / OpenGL scene here

        m_Framebuffer->Unbind();
        // --------------------------------------

        // Display the FBO color texture inside the ImGui panel.
        // UV coords are flipped vertically because OpenGL's origin is bottom-left.
        ImGui::Image(
            (ImTextureID)(intptr_t)m_Framebuffer->GetColorAttachment(),
            viewportSize,
            ImVec2(0, 1),   // top-left  UV
            ImVec2(1, 0)    // bottom-right UV
        );
    }

    ImGui::End();
}

} // namespace AnimView
