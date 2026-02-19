#pragma once

#include <memory>
#include "Window.h"

namespace AnimView {

// Forward declarations
class UILayer;
class AnimationPlayer;

class Application {
public:
    Application();
    ~Application();

    // Delete copy constructor and assignment operator
    Application(const Application&) = delete;
    Application& operator=(const Application&) = delete;

    void Run();
    
    Window* GetWindow() const { return m_Window.get(); }

private:
    void Update();
    void Render();

private:
    std::unique_ptr<Window> m_Window;
    std::unique_ptr<UILayer> m_UILayer;
    std::unique_ptr<AnimationPlayer> m_AnimationPlayer;
    
    bool m_Running = true;
};

} // namespace AnimView
