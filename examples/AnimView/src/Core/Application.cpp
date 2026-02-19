#include "Application.h"
#include "../UI/UILayer.h"
#include "../Animation/AnimationPlayer.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace AnimView {

Application::Application() {
    // Create window
    m_Window = std::make_unique<Window>(1280, 720, "Animate Atlas Viewer");
    m_AnimationPlayer = std::make_unique<AnimationPlayer>();
    m_UILayer = std::make_unique<UILayer>(m_Window.get(), m_AnimationPlayer.get());
}

Application::~Application() {}

void Application::Run() {
    while (!m_Window->ShouldClose() && m_Running) {
        Update();
        Render();
        
        m_Window->SwapBuffers();
        m_Window->PollEvents();
    }
}

void Application::Update() {
    m_AnimationPlayer->Update();
}

void Application::Render() {
    // Clear screen
    glClear(GL_COLOR_BUFFER_BIT);
    
    // Render UI
    m_UILayer->Begin();
    m_UILayer->Render();
    m_UILayer->End();
}

} // namespace AnimView
