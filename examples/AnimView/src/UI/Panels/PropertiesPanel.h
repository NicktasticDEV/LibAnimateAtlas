#pragma once

#include "../UILayer.h"
#include <string>

namespace AnimView {

class PropertiesPanel : public IPanel {
public:
    PropertiesPanel() = default;
    ~PropertiesPanel() override = default;

    void OnImGuiRender() override;
};

} // namespace AnimView
