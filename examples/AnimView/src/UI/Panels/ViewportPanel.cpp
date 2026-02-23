#include "ViewportPanel.h"

#include <imgui.h>
#include <glad/glad.h>

namespace AnimView {

// OpenGL Temporary stuff for testing the FBO display; replace with your actual rendering code
const char *vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";
const char *fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);\n"
"}\n\0";

unsigned int vertexShader;
unsigned int fragmentShader;
unsigned int shaderProgram;
unsigned int VBO, VAO;

ViewportPanel::ViewportPanel()
{
    // Create an initial framebuffer; it will be resized on the first frame
    m_Framebuffer = std::make_unique<Framebuffer>(1, 1);

    // Initialize OpenGL resources for testing the FBO display; replace with your actual rendering code
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    float vertices[] = {
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.5f,  0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f,
         0.5f,  0.5f, 0.0f,
        -0.5f,  0.5f, 0.0f
    };
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
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
        // Temporary test draw (replace with your actual rendering code)
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        glBindVertexArray(0);
        glUseProgram(0);

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
