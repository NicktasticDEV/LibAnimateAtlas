#pragma once

#include "../UILayer.h"

namespace AnimView {

class ViewportPanel : public IPanel {
public:
    ViewportPanel() = default;
    ~ViewportPanel() override = default;

    void OnImGuiRender() override;
};

} // namespace AnimView
