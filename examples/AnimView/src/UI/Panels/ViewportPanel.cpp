#include "ViewportPanel.h"

#include <imgui.h>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace AnimView {

// Temporary test shaders; replace with your actual rendering code
static const char* s_VertexSrc = R"(
#version 330 core
layout (location = 0) in vec3 aPos;
uniform mat4 u_MVP;
void main()
{
    gl_Position = u_MVP * vec4(aPos, 1.0);
}
)";

static const char* s_FragmentSrc = R"(
#version 330 core
out vec4 FragColor;
void main()
{
    FragColor = vec4(1.0, 1.0, 1.0, 1.0);
}
)";

ViewportPanel::ViewportPanel()
{
    // Create an initial framebuffer; it will be resized on the first frame
    m_Framebuffer = std::make_unique<Framebuffer>(1, 1);

    // Compile shader program
    m_Shader = std::make_unique<Shader>(s_VertexSrc, s_FragmentSrc);

    // Initialize test geometry
    glGenVertexArrays(1, &m_VAO);
    glGenBuffers(1, &m_VBO);

    glBindVertexArray(m_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    float vertices[] = {
        -1.00f, -1.00f, 0.0f,
         1.00f, -1.00f, 0.0f,
         1.00f,  1.00f, 0.0f,
        -1.00f, -1.00f, 0.0f,
         1.00f,  1.00f, 0.0f,
        -1.00f,  1.00f, 0.0f
    };
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

ViewportPanel::~ViewportPanel()
{
    glDeleteBuffers(1, &m_VBO);
    glDeleteVertexArrays(1, &m_VAO);
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

        // Projection
        glm::mat4 projection = glm::ortho(0.0f, (float)vpW, -(float)vpH, 0.0f, -1.0f, 1.0f);
        // View
        glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));

        glm::mat4 mvp = projection * view;

        //* Temporary test draw (replace with your actual rendering code)
        m_Shader->Bind();
        m_Shader->SetMat4("u_MVP", mvp);
        glBindVertexArray(m_VAO);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        glBindVertexArray(0);
        m_Shader->Unbind();

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
