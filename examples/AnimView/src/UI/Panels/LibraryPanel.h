#pragma once

#include "../UILayer.h"
#include <string>

namespace AnimView {

class LibraryPanel : public IPanel {
public:
    LibraryPanel() = default;
    ~LibraryPanel() override = default;

    void OnImGuiRender() override;

private:
    std::string m_CurrentAnimation = "NONE";
};

} // namespace AnimView
