#pragma once

#include <vector>
#include <memory>

namespace AnimView {

// Forward declarations
class Window;
class AnimationPlayer;

// Base class for ImGui UIs
class IPanel {
public:
    virtual ~IPanel() = default;

    // Call every frame
    virtual void OnImGuiRender() = 0;

    void SetOpen(bool isOpen) { m_IsOpen = isOpen; }
    bool IsOpen() const { return m_IsOpen; }

protected:
    bool m_IsOpen = true;
};

class UILayer {
public:
    UILayer(Window* window, AnimationPlayer* player);
    ~UILayer();

    // Delete copy constructor and assignment operator
    UILayer(const UILayer&) = delete;
    UILayer& operator=(const UILayer&) = delete;

    void Begin();
    void Render();
    void End();

    // To add panels to UI view
    template<typename T>
    void AddPanel() {
        m_Panels.push_back(std::make_shared<T>());
    }

    AnimationPlayer* GetAnimationPlayer() const { return m_AnimationPlayer; }

private:
    void InitializeImGui();
    void ShutdownImGui();
    void SetupDockspace();

private:
    Window* m_Window;
    AnimationPlayer* m_AnimationPlayer;
    std::vector<std::shared_ptr<IPanel>> m_Panels;
    bool m_Initialized = false;
    bool m_DockspaceInitialized = false;
};

} // namespace AnimView
