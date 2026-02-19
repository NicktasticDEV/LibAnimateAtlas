#pragma once

#include "../UILayer.h"

namespace AnimView {

class TimelinePanel : public IPanel {
public:
    TimelinePanel() = default;
    ~TimelinePanel() override = default;

    void OnImGuiRender() override;

private:
    int m_TimelineScrubber = 0.0f;
};

} // namespace AnimView
