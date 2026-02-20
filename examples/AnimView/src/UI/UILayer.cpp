#include "UILayer.h"

#include "../Core/Window.h"

// UI Panels used by app
#include "Panels/LibraryPanel.h"
#include "Panels/ViewportPanel.h"
#include "Panels/TimelinePanel.h"
#include "Panels/PropertiesPanel.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <imgui.h>
#include <imgui_internal.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

namespace AnimView {

UILayer::UILayer(Window* window) : m_Window(window)
{
    InitializeImGui();
    
    // Register default panels
    AddPanel<ViewportPanel>();
    AddPanel<TimelinePanel>();
    AddPanel<LibraryPanel>();
    AddPanel<PropertiesPanel>();
}

UILayer::~UILayer() {
    ShutdownImGui();
}

void UILayer::InitializeImGui() {
    if (m_Initialized)
        return;

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    
    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(m_Window->GetNativeWindow(), true);
    ImGui_ImplOpenGL3_Init("#version 150");

    m_Initialized = true;
}

void UILayer::ShutdownImGui() {
    if (!m_Initialized)
        return;

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    m_Initialized = false;
}

void UILayer::SetupDockspace() {
    // Create a fullscreen dockspace
    ImGuiViewport* viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(viewport->WorkPos);
    ImGui::SetNextWindowSize(viewport->WorkSize);
    ImGui::SetNextWindowViewport(viewport->ID);
    
    ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
    window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse;
    window_flags |= ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
    window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
    
    ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
    
    ImGui::Begin("DockSpace", nullptr, window_flags);
    ImGui::PopStyleVar(3);
    
    // DockSpace
    ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
    ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), ImGuiDockNodeFlags_None);
    
    // Default dock view
    if (!m_DockspaceInitialized) {
        m_DockspaceInitialized = true;
        
        ImGui::DockBuilderRemoveNode(dockspace_id); // Clear any existing layout
        ImGui::DockBuilderAddNode(dockspace_id, ImGuiDockNodeFlags_DockSpace);
        ImGui::DockBuilderSetNodeSize(dockspace_id, viewport->Size);
        
        // Dockspace split
        ImGuiID dock_main_id = dockspace_id;
        ImGuiID dock_id_right = ImGui::DockBuilderSplitNode(dock_main_id, ImGuiDir_Right, 0.25f, nullptr, &dock_main_id);
        ImGuiID dock_id_bottom = ImGui::DockBuilderSplitNode(dock_main_id, ImGuiDir_Down, 0.3f, nullptr, &dock_main_id);
        
        // Dock windows
        ImGui::DockBuilderDockWindow("Viewport", dock_main_id);     // Center
        ImGui::DockBuilderDockWindow("Library", dock_id_right);     // Right
        ImGui::DockBuilderDockWindow("Properties", dock_id_right);   // Right (stacked with Library)
        ImGui::DockBuilderDockWindow("Timeline", dock_id_bottom);   // Bottom
        
        ImGui::DockBuilderFinish(dockspace_id);
    }
    
    // Menu bar
    if (ImGui::BeginMenuBar()) {

        // File
        if (ImGui::BeginMenu("File")) {
            if (ImGui::MenuItem("New")) {}
            if (ImGui::MenuItem("Open")) {}
            if (ImGui::MenuItem("Close")) {}
            ImGui::EndMenu();
        }

        // View
        if (ImGui::BeginMenu("View")) {
            //TODO: Make it so that instead of hardcoding the panels, we just register the panels and have them just be listed in the menu
            bool viewport_open = m_Panels[0]->IsOpen();
            bool timeline_open = m_Panels[1]->IsOpen();
            bool library_open = m_Panels[2]->IsOpen();
            bool properties_open = m_Panels[3]->IsOpen();
            if (ImGui::MenuItem("Viewport", nullptr, &viewport_open)) {
                m_Panels[0]->SetOpen(viewport_open);
            }
            if (ImGui::MenuItem("Timeline", nullptr, &timeline_open)) {
                m_Panels[1]->SetOpen(timeline_open);
            }
            if (ImGui::MenuItem("Library", nullptr, &library_open)) {
                m_Panels[2]->SetOpen(library_open);
            }
            if (ImGui::MenuItem("Properties", nullptr, &properties_open)) {
                m_Panels[3]->SetOpen(properties_open);
            }

            ImGui::EndMenu();
        }

        ImGui::EndMenuBar();

    }
    
    ImGui::End();
}

void UILayer::Begin() {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void UILayer::Render() {
    // Create main dockspace
    SetupDockspace();
    
    // Render all registered panels
    for (auto& panel : m_Panels) {
        if (panel->IsOpen()) {
            panel->OnImGuiRender();
        }
    }
}

void UILayer::End() {
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

} // namespace AnimView
