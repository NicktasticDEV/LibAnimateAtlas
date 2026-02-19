#pragma once

#include "../UILayer.h"
#include <string>

namespace AnimView {

class InspectorPanel : public IPanel {
public:
    InspectorPanel() = default;
    ~InspectorPanel() override = default;

    void OnImGuiRender() override;

private:
    std::string m_CurrentAnimation = "NONE";
    float m_Duration = 1.5f;
};

} // namespace AnimView
