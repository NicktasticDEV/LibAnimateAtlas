#pragma once

#include "../UILayer.h"
#include <string>

namespace AnimView {

class SpriteMapPanel : public IPanel {
public:
    SpriteMapPanel() = default;
    ~SpriteMapPanel() override = default;

    void OnImGuiRender() override;
};

} // namespace AnimView
