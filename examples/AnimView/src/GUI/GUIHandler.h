#pragma once

#include <string>

struct GLFWwindow;

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include <vector>
#include <memory>

// Abstract base class for all editor panels
class IPanel {
public:
    virtual ~IPanel() = default;

    // Called every frame to draw the specific ImGui widgets
    virtual void OnImGuiRender() = 0;

    // Set whether the window is visible
    void SetOpen(bool isOpen) { m_IsOpen = isOpen; }
    bool IsOpen() const { return m_IsOpen; }

protected:
    bool m_IsOpen = true;
};





class GuiLayer {
public:
    GuiLayer() = default;
    ~GuiLayer() { Shutdown(); }

    // 1. Initialize ImGui (Context, Style, Backends)
    void Init(void* windowHandle) {
        if (m_Initialized)
            return;

        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO();
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable; // Crucial for editors!
        
        // Setup style (Dark theme is standard for editors)
        ImGui::StyleColorsDark();

        ImGui_ImplGlfw_InitForOpenGL(static_cast<GLFWwindow*>(windowHandle), true);
        ImGui_ImplOpenGL3_Init("#version 130");

        m_Initialized = true;
    }

    // 2. Start a new frame
    void Begin() {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
    }

    // 3. Render all registered panels
    void RenderPanels() {
        for (auto& panel : m_Panels) {
            if (panel->IsOpen()) {
                panel->OnImGuiRender();
            }
        }
    }

    // 4. End frame and render to screen
    void End() {
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        
        // Handle Viewports if enabled (for multi-window support)
        ImGuiIO& io = ImGui::GetIO();
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            // Update and Render additional Platform Windows
            GLFWwindow* backup_current_context = glfwGetCurrentContext();
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
            glfwMakeContextCurrent(backup_current_context);
        }
    }

    // Clean up
    void Shutdown() {
        if (!m_Initialized)
            return;

        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();

        m_Initialized = false;
    }

    // Helper to add panels easily
    template<typename T>
    void AddPanel() {
        m_Panels.push_back(std::make_shared<T>());
    }

private:
    std::vector<std::shared_ptr<IPanel>> m_Panels;
    bool m_Initialized = false;
};