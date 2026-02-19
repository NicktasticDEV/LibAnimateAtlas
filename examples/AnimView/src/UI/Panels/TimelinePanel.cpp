#include "TimelinePanel.h"
#include <imgui.h>

namespace AnimView {

TimelinePanel::TimelinePanel() {
    // Initialize dummy data - Flash/Animate style timeline
    /*
        DATA STRUCTURE
        {
            name: "Layer 1",
            keyframes: [
                { frame: 0, isTween: false },
                { frame: 5, isTween: true },
                { frame: 10, isTween: false },
                ...
            ],
            visible: true,
            locked: false
        },
    */
    m_Layers = {
        {"Test", {{0, false}, {15, false}, {16, false}, {17, false}, {18, false}, {30, true}, {45, false}}, true, false},
        {"Test2", {{0, false}, {5, true}, {10, false}, {20, true}, {30, false}}, true, false},
        {"Test3", {{10, false}, {25, false}, {40, false}}, true, false},
        {"Test4", {{0, false}, {30, false}}, true, false}
    };
    
    // Sort keyframes by frame number for each layer
    for (auto& layer : m_Layers) {
        std::sort(layer.keyframes.begin(), layer.keyframes.end(), 
            [](const Keyframe& a, const Keyframe& b) { return a.frame < b.frame; });
    }
}

void TimelinePanel::OnImGuiRender() {
    if (!ImGui::Begin("Timeline", &m_IsOpen)) {
        ImGui::End();
        return;
    }
    
    // Playback controls
    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(8.0f, 4.0f));
    if (ImGui::Button("<<")) { m_CurrentFrame = 0; }
    ImGui::SameLine();
    if (ImGui::Button("<")) { if (m_CurrentFrame > 0) m_CurrentFrame--; }
    ImGui::SameLine();
    if (ImGui::Button(">")) { if (m_CurrentFrame < m_TotalFrames - 1) m_CurrentFrame++; }
    ImGui::SameLine();
    if (ImGui::Button(">>")) { m_CurrentFrame = m_TotalFrames - 1; }
    ImGui::SameLine();
    if (ImGui::Button("Play")) {}
    ImGui::SameLine();
    ImGui::Text("Frame: %d/%d", m_CurrentFrame, m_TotalFrames - 1);
    ImGui::PopStyleVar();
    
    ImGui::Separator();
    
    // Timeline dimensions (using appearance settings)
    const float layerNameWidth = m_Appearance.layerNameWidth;
    const float cellWidth = m_Appearance.cellWidth * m_Zoom;
    const float rowHeight = m_Appearance.rowHeight;
    const float timelineWidth = m_TotalFrames * cellWidth;
    
    // Timeline scrollable area
    ImGui::BeginChild("TimelineContent", ImVec2(0, 0), true, ImGuiWindowFlags_HorizontalScrollbar);
    
    // Draw frame ruler
    DrawFrameRuler(timelineWidth, cellWidth);
    
    // Draw layers
    DrawLayers(layerNameWidth, timelineWidth, cellWidth, rowHeight);
    
    // Draw playhead (on top of everything)
    DrawPlayhead(timelineWidth, cellWidth);
    
    ImGui::EndChild();
    
    ImGui::End();
}

void TimelinePanel::DrawFrameRuler(float timelineWidth, float cellWidth) {
    ImDrawList* drawList = ImGui::GetWindowDrawList();
    ImVec2 cursorPos = ImGui::GetCursorScreenPos();
    const float layerNameWidth = m_Appearance.layerNameWidth;
    const float rulerHeight = m_Appearance.rulerHeight;
    
    // Background for ruler
    drawList->AddRectFilled(
        cursorPos,
        ImVec2(cursorPos.x + layerNameWidth + timelineWidth, cursorPos.y + rulerHeight),
        m_Appearance.colors.rulerBackground
    );
    
    // Draw frame numbers and tick marks
    for (int frame = 0; frame < m_TotalFrames; frame++) {
        float x = cursorPos.x + layerNameWidth + frame * cellWidth;
        
        // Draw tick marks every frame
        drawList->AddLine(
            ImVec2(x, cursorPos.y + rulerHeight - 4),
            ImVec2(x, cursorPos.y + rulerHeight),
            IM_COL32(100, 100, 100, 255)
        );
        
        // Draw frame numbers every 5 frames
        if (frame % 5 == 0) {
            drawList->AddLine(
                ImVec2(x, cursorPos.y + rulerHeight - 8),
                ImVec2(x, cursorPos.y + rulerHeight),
                IM_COL32(150, 150, 150, 255)
            );
            
            char frameNum[8];
            snprintf(frameNum, sizeof(frameNum), "%d", frame);
            drawList->AddText(
                ImVec2(x + 2, cursorPos.y + 2),
                IM_COL32(200, 200, 200, 255),
                frameNum
            );
        }
    }
    
    ImGui::Dummy(ImVec2(layerNameWidth + timelineWidth, rulerHeight));
}

void TimelinePanel::DrawLayers(float layerNameWidth, float timelineWidth, float cellWidth, float rowHeight) {
    ImDrawList* drawList = ImGui::GetWindowDrawList();
    ImVec2 startPos = ImGui::GetCursorScreenPos();
    
    for (size_t i = 0; i < m_Layers.size(); i++) {
        ImVec2 rowPos = ImVec2(startPos.x, startPos.y + i * rowHeight);
        
        // Layer name background
        drawList->AddRectFilled(
            rowPos,
            ImVec2(rowPos.x + layerNameWidth, rowPos.y + rowHeight),
            m_Appearance.colors.layerBackground
        );
        
        // Layer name border
        drawList->AddRect(
            rowPos,
            ImVec2(rowPos.x + layerNameWidth, rowPos.y + rowHeight),
            m_Appearance.colors.layerBorder
        );
        
        // Layer name text
        drawList->AddText(
            ImVec2(rowPos.x + 5, rowPos.y + 5),
            IM_COL32(220, 220, 220, 255),
            m_Layers[i].name.c_str()
        );
        
        const auto& layer = m_Layers[i];
        const float cellPadding = m_Appearance.cellPadding;
        
        // First, draw empty frame background for entire row
        drawList->AddRectFilled(
            ImVec2(rowPos.x + layerNameWidth, rowPos.y),
            ImVec2(rowPos.x + layerNameWidth + timelineWidth, rowPos.y + rowHeight),
            m_Appearance.colors.emptyFrame
        );
        
        // Draw keyframe spans as continuous shapes
        for (size_t k = 0; k < layer.keyframes.size(); k++) {
            const auto& keyframe = layer.keyframes[k];
            int startFrame = keyframe.frame;
            int endFrame = (k + 1 < layer.keyframes.size()) ? 
                layer.keyframes[k + 1].frame : m_TotalFrames;
            
            float startX = rowPos.x + layerNameWidth + startFrame * cellWidth;
            float endX = rowPos.x + layerNameWidth + endFrame * cellWidth;
            
            // Choose color based on tween status
            ImU32 spanColor = keyframe.isTween ? 
                m_Appearance.colors.tweenKeyframe : 
                m_Appearance.colors.normalKeyframe;
            
            // Draw the continuous span
            drawList->AddRectFilled(
                ImVec2(startX + cellPadding, rowPos.y + cellPadding),
                ImVec2(endX - cellPadding, rowPos.y + rowHeight - cellPadding),
                spanColor
            );
            
        }
        
        // Draw grid lines on top
        if (m_Appearance.showGridLines) {
            for (int frame = 0; frame <= m_TotalFrames; frame++) {
                float x = rowPos.x + layerNameWidth + frame * cellWidth;
                
                // Draw stronger lines every 5 frames
                if (frame % 5 == 0) {
                    drawList->AddLine(
                        ImVec2(x, rowPos.y),
                        ImVec2(x, rowPos.y + rowHeight),
                        m_Appearance.colors.gridLine5Frame,
                        m_Appearance.gridLineThickness5Frame
                    );
                } else {
                    drawList->AddLine(
                        ImVec2(x, rowPos.y),
                        ImVec2(x, rowPos.y + rowHeight),
                        m_Appearance.colors.gridLine,
                        m_Appearance.gridLineThickness
                    );
                }
            }
        }
        
        // Draw circles at keyframe positions on top of everything
        for (const auto& keyframe : layer.keyframes) {
            float x = rowPos.x + layerNameWidth + keyframe.frame * cellWidth;
            float circleX = x + cellWidth * 0.5f;
            //float circleY = rowPos.y + rowHeight - 6.0f;
            float circleY;
            if (m_Appearance.keyframeCircleCentered) {
                circleY = rowPos.y + rowHeight * 0.5f;
            } else {
                circleY = rowPos.y + rowHeight - 6.0f;
            }

            // Draw filled circle
            drawList->AddCircleFilled(
                ImVec2(circleX, circleY),
                m_Appearance.keyframeCircleRadius,
                m_Appearance.colors.keyframeCircleFill
            );
            
            // Draw circle outline
            drawList->AddCircle(
                ImVec2(circleX, circleY),
                m_Appearance.keyframeCircleRadius,
                m_Appearance.colors.keyframeCircleOutline,
                0,
                m_Appearance.keyframeCircleThickness
            );
        }
        
        // Horizontal separator
        drawList->AddLine(
            ImVec2(rowPos.x, rowPos.y + rowHeight),
            ImVec2(rowPos.x + layerNameWidth + timelineWidth, rowPos.y + rowHeight),
            m_Appearance.colors.layerBorder
        );
    }
    
    ImGui::Dummy(ImVec2(layerNameWidth + timelineWidth, m_Layers.size() * rowHeight));
}

void TimelinePanel::DrawPlayhead(float timelineWidth, float cellWidth) {
    ImDrawList* drawList = ImGui::GetWindowDrawList();
    const float layerNameWidth = m_Appearance.layerNameWidth;
    const float rulerHeight = m_Appearance.rulerHeight;
    const float rowHeight = m_Appearance.rowHeight;
    
    // Get the current scroll-adjusted cursor position
    ImVec2 timelineStart = ImGui::GetCursorScreenPos();
    // Move back up to where the ruler starts
    timelineStart.y -= (m_Layers.size() * rowHeight + rulerHeight);
    
    float playheadX = timelineStart.x + layerNameWidth + m_CurrentFrame * cellWidth + (cellWidth / 2);
    float timelineHeight = rulerHeight + m_Layers.size() * rowHeight;
    
    // Playhead line (red, like Flash)
    drawList->AddLine(
        ImVec2(playheadX, timelineStart.y),
        ImVec2(playheadX, timelineStart.y + timelineHeight),
        m_Appearance.colors.playhead,
        m_Appearance.playheadThickness
    );
    
    // Playhead handle at the top (triangle)
    const float triangleSize = m_Appearance.playheadTriangleSize;
    ImVec2 trianglePoints[3] = {
        ImVec2(playheadX - triangleSize, timelineStart.y),
        ImVec2(playheadX + triangleSize, timelineStart.y),
        ImVec2(playheadX, timelineStart.y + 10)
    };
    drawList->AddTriangleFilled(
        trianglePoints[0],
        trianglePoints[1],
        trianglePoints[2],
        m_Appearance.colors.playhead
    );
}

} // namespace AnimView
