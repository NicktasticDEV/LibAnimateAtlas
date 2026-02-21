#include "UILayer.h"

#include "../Core/Window.h"

// UI Panels used by app
#include "Panels/LibraryPanel.h"
#include "Panels/ViewportPanel.h"
#include "Panels/TimelinePanel.h"
#include "Panels/PropertiesPanel.h"

// Other shit
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
    
    ApplyCustomTheme();

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

void UILayer::ApplyCustomTheme() {
    ImVec4* colors = ImGui::GetStyle().Colors;

    colors[ImGuiCol_Text]                   = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
    colors[ImGuiCol_TextDisabled]           = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
    colors[ImGuiCol_WindowBg]               = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
    colors[ImGuiCol_ChildBg]                = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    colors[ImGuiCol_PopupBg]                = ImVec4(0.08f, 0.08f, 0.08f, 0.94f);
    colors[ImGuiCol_Border]                 = ImVec4(0.29f, 0.29f, 0.29f, 1.00f);
    colors[ImGuiCol_BorderShadow]           = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    colors[ImGuiCol_FrameBg]                = ImVec4(0.18f, 0.18f, 0.18f, 1.00f);
    colors[ImGuiCol_FrameBgHovered]         = ImVec4(0.26f, 0.59f, 0.98f, 0.40f);
    colors[ImGuiCol_FrameBgActive]          = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
    colors[ImGuiCol_TitleBg]                = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
    colors[ImGuiCol_TitleBgActive]          = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
    colors[ImGuiCol_TitleBgCollapsed]       = ImVec4(0.00f, 0.00f, 0.00f, 0.51f);
    colors[ImGuiCol_MenuBarBg]              = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);
    colors[ImGuiCol_ScrollbarBg]            = ImVec4(0.02f, 0.02f, 0.02f, 0.00f);
    colors[ImGuiCol_ScrollbarGrab]          = ImVec4(0.38f, 0.38f, 0.38f, 1.00f);
    colors[ImGuiCol_ScrollbarGrabHovered]   = ImVec4(0.41f, 0.41f, 0.41f, 1.00f);
    colors[ImGuiCol_ScrollbarGrabActive]    = ImVec4(0.51f, 0.51f, 0.51f, 1.00f);
    colors[ImGuiCol_CheckMark]              = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
    colors[ImGuiCol_SliderGrab]             = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
    colors[ImGuiCol_SliderGrabActive]       = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
    colors[ImGuiCol_Button]                 = ImVec4(0.18f, 0.18f, 0.18f, 1.00f);
    colors[ImGuiCol_ButtonHovered]          = ImVec4(0.10f, 0.10f, 0.10f, 1.00f);
    colors[ImGuiCol_ButtonActive]           = ImVec4(0.06f, 0.53f, 0.98f, 1.00f);
    colors[ImGuiCol_Header]                 = ImVec4(0.18f, 0.18f, 0.18f, 1.00f);
    colors[ImGuiCol_HeaderHovered]          = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
    colors[ImGuiCol_HeaderActive]           = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
    colors[ImGuiCol_Separator]              = ImVec4(0.15f, 0.15f, 0.15f, 1.00f);
    colors[ImGuiCol_SeparatorHovered]       = ImVec4(0.10f, 0.40f, 0.75f, 1.00f);
    colors[ImGuiCol_SeparatorActive]        = ImVec4(0.10f, 0.40f, 0.75f, 1.00f);
    colors[ImGuiCol_ResizeGrip]             = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
    colors[ImGuiCol_ResizeGripHovered]      = ImVec4(0.61f, 0.79f, 1.00f, 1.00f);
    colors[ImGuiCol_ResizeGripActive]       = ImVec4(0.00f, 0.27f, 0.59f, 1.00f);
    colors[ImGuiCol_InputTextCursor]        = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
    colors[ImGuiCol_TabHovered]             = ImVec4(0.64f, 0.64f, 0.64f, 1.00f);
    colors[ImGuiCol_Tab]                    = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
    colors[ImGuiCol_TabSelected]            = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
    colors[ImGuiCol_TabSelectedOverline]    = ImVec4(0.26f, 0.59f, 0.98f, 0.00f);
    colors[ImGuiCol_TabDimmed]              = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
    colors[ImGuiCol_TabDimmedSelected]      = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
    colors[ImGuiCol_TabDimmedSelectedOverline]  = ImVec4(0.50f, 0.50f, 0.50f, 0.00f);
    colors[ImGuiCol_DockingPreview]         = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
    colors[ImGuiCol_DockingEmptyBg]         = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
    colors[ImGuiCol_PlotLines]              = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
    colors[ImGuiCol_PlotLinesHovered]       = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
    colors[ImGuiCol_PlotHistogram]          = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
    colors[ImGuiCol_PlotHistogramHovered]   = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
    colors[ImGuiCol_TableHeaderBg]          = ImVec4(0.19f, 0.19f, 0.20f, 1.00f);
    colors[ImGuiCol_TableBorderStrong]      = ImVec4(0.31f, 0.31f, 0.35f, 1.00f);
    colors[ImGuiCol_TableBorderLight]       = ImVec4(0.23f, 0.23f, 0.25f, 1.00f);
    colors[ImGuiCol_TableRowBg]             = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    colors[ImGuiCol_TableRowBgAlt]          = ImVec4(1.00f, 1.00f, 1.00f, 0.06f);
    colors[ImGuiCol_TextLink]               = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
    colors[ImGuiCol_TextSelectedBg]         = ImVec4(0.26f, 0.59f, 0.98f, 0.35f);
    colors[ImGuiCol_TreeLines]              = ImVec4(0.43f, 0.43f, 0.50f, 0.50f);
    colors[ImGuiCol_DragDropTarget]         = ImVec4(1.00f, 1.00f, 0.00f, 0.90f);
    colors[ImGuiCol_DragDropTargetBg]       = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    colors[ImGuiCol_UnsavedMarker]          = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
    colors[ImGuiCol_NavCursor]              = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
    colors[ImGuiCol_NavWindowingHighlight]  = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
    colors[ImGuiCol_NavWindowingDimBg]      = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
    colors[ImGuiCol_ModalWindowDimBg]       = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);

    // Apply style settings
    ImGuiStyle& style = ImGui::GetStyle();
    
    // Main
    style.WindowPadding                     = ImVec2(8.00f, 8.00f);
    style.FramePadding                      = ImVec2(6.00f, 6.00f);
    style.ItemSpacing                       = ImVec2(8.00f, 4.00f);
    style.ItemInnerSpacing                  = ImVec2(4.00f, 4.00f);
    style.IndentSpacing                     = 21.00f;
    style.CellPadding                       = ImVec2(4.00f, 2.00f);
    
    // Borders
    //style.BorderSize                        = 1.00f;
    style.ChildBorderSize                   = 1.00f;
    style.PopupBorderSize                   = 1.00f;
    style.FrameBorderSize                   = 1.00f;
    style.TabBorderSize                     = 0.00f;
    
    // Rounding
    style.WindowRounding                    = 5.00f;
    style.ChildRounding                     = 0.00f;
    style.FrameRounding                     = 5.00f;
    style.PopupRounding                     = 5.00f;
    style.ScrollbarRounding                 = 12.00f;
    style.GrabRounding                      = 4.00f;
    style.TabRounding                       = 0.00f;
    
    // Scrollbar
    style.ScrollbarSize                     = 10.00f;
    style.GrabMinSize                       = 10.00f;
    
    // Tabs
    style.TabBarBorderSize                  = 1.00f;
    
    // Windows
    style.WindowMenuButtonPosition          = ImGuiDir_Right;
    
    // Widgets
    style.ButtonTextAlign                   = ImVec2(0.50f, 0.50f);
    style.SelectableTextAlign               = ImVec2(0.00f, 0.00f);
    style.SeparatorTextBorderSize           = 3.00f;
    style.SeparatorTextAlign                = ImVec2(0.00f, 0.50f);
    style.SeparatorTextPadding              = ImVec2(20.00f, 3.00f);
    style.DisplayWindowPadding              = ImVec2(19.00f, 19.00f);
    style.DisplaySafeAreaPadding            = ImVec2(3.00f, 3.00f);
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
    
    ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
    ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), ImGuiDockNodeFlags_None);
    
    // Default dock set up
    if (!m_DockspaceInitialized) {
        m_DockspaceInitialized = true;
        
        // Dockspace init
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
        ImGui::DockBuilderDockWindow("Properties", dock_id_right);  // Right (stacked with Library)
        ImGui::DockBuilderDockWindow("Timeline", dock_id_bottom);   // Bottom
        
        ImGui::DockBuilderFinish(dockspace_id);
    }
    
    // Menu bar
    if (ImGui::BeginMenuBar()) {

        // File
        if (ImGui::BeginMenu("File")) {
            //if (ImGui::MenuItem("New")) {}
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

    SetupDockspace();

    // Render ImGUI demo
    //ImGui::ShowDemoWindow();

    // Render panels
    for (auto& panel : m_Panels) {
        if (panel->IsOpen()) {
            panel->OnImGuiRender();
        }
    }

}

void UILayer::End() {
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    
    // Handle Viewports
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
