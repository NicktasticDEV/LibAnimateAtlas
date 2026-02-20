#pragma once

#include "../UILayer.h"
#include "../../Core/Framebuffer.h"

#include <memory>

namespace AnimView {

class ViewportPanel : public IPanel {
public:
    ViewportPanel();
    ~ViewportPanel() override = default;

    void OnImGuiRender() override;

private:
    std::unique_ptr<Framebuffer> m_Framebuffer;
};

} // namespace AnimView
