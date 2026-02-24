#pragma once

#include "../UILayer.h"
#include "../../Core/Framebuffer.h"
#include "../../Core/Shader.h"

#include <memory>

namespace AnimView {

class ViewportPanel : public IPanel {
public:
    ViewportPanel();
    ~ViewportPanel() override;

    void OnImGuiRender() override;

private:
    std::unique_ptr<Framebuffer> m_Framebuffer;
    std::unique_ptr<Shader>      m_Shader;

    // OpenGL resources (temporary test geometry)
    unsigned int m_VAO = 0;
    unsigned int m_VBO = 0;
};

} // namespace AnimView
