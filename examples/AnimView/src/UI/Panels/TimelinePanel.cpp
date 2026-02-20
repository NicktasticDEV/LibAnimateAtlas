#include "TimelinePanel.h"
#include <imgui.h>
#include <algorithm>

namespace AnimView {

TimelinePanel::TimelinePanel() {

    // Test data
    m_Layers = {
        // Structure: Layer name, list of keyframes (frame number, number of elements, isTween), visible
        {"Test", {{0, 1, false}, {15, 0, false}, {16, 0, false}, {17, 1, false}, {18, 1, false}, {30, 1, true}, {45, 1, false}}, true},
        {"Test2", {{0, 1, false}, {5, 1, true}, {10, 1, false}, {20, 1, true}, {30, 1, false}}, true},
        {"Test3", {{0, 0, false}, {10, 1, false}, {25, 1, false}, {40, 1, false}}, true},
        {"Test4", {{0, 0, false}, {30, 1, false}}, true}
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

    // Compute last keyframe across all layers (dynamic end frame, like Adobe Animate)
    int lastKeyframe = 0;
    for (const auto& layer : m_Layers)
        for (const auto& kf : layer.keyframes)
            lastKeyframe = std::max(lastKeyframe, kf.frame);

    // Playback controls
    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(8.0f, 4.0f));
    if (ImGui::Button("<<")) { m_CurrentFrame = 0; }
    ImGui::SameLine();
    if (ImGui::Button("<")) { if (m_CurrentFrame > 0) m_CurrentFrame--; }
    ImGui::SameLine();
    if (ImGui::Button(">")) { if (m_CurrentFrame < lastKeyframe) m_CurrentFrame++; }
    ImGui::SameLine();
    if (ImGui::Button(">>")) { m_CurrentFrame = lastKeyframe; }
    ImGui::SameLine();
    if (ImGui::Button("Play")) {}
    ImGui::SameLine();
    ImGui::Text("Frame: %d", m_CurrentFrame);
    ImGui::PopStyleVar();

    ImGui::Separator();

    const float layerNameWidth = m_Appearance.layerNameWidth;
    const float cellWidth      = m_Appearance.cellWidth * m_Zoom;
    const float rowHeight      = m_Appearance.rowHeight;

    // Available width for the frame grid (excludes the pinned layer-name column)
    float availableWidth = ImGui::GetContentRegionAvail().x - layerNameWidth;
    if (availableWidth < 1.0f) availableWidth = 1.0f;
    int visibleFrames = std::max(1, (int)(availableWidth / cellWidth));

    // Limit scroll so the user cannot pan past the last keyframe (+small buffer)
    int maxOffset = std::max(0, lastKeyframe + 500);
    m_FrameOffset = std::max(0, std::min(m_FrameOffset, maxOffset));

    // Auto-scroll (Adobe Animate style): keep the playhead in view when stepping
    if (m_CurrentFrame < m_FrameOffset) {
        m_FrameOffset = m_CurrentFrame;
    } else if (m_CurrentFrame >= m_FrameOffset + visibleFrames) {
        m_FrameOffset = m_CurrentFrame - visibleFrames + 1;
        m_FrameOffset = std::min(m_FrameOffset, maxOffset);
    }

    // Timeline child — no ImGui scroll bars; we manage panning ourselves
    ImGui::BeginChild("TimelineContent", ImVec2(0, 0), true,
        ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse);

    // Mouse-wheel panning (vertical wheel scrolls the timeline horizontally)
    if (ImGui::IsWindowHovered()) {
        float wheel = ImGui::GetIO().MouseWheelH;
        if (wheel == 0.0f) wheel = -ImGui::GetIO().MouseWheel; // fallback to vertical wheel
        if (wheel != 0.0f) {
            int delta = (wheel > 0) ? 3 : -3;
            m_FrameOffset = std::max(0, std::min(m_FrameOffset + delta, maxOffset));
        }
    }

    DrawFrameRuler(availableWidth, cellWidth);
    DrawLayers(layerNameWidth, availableWidth, cellWidth, rowHeight);
    DrawPlayhead(availableWidth, cellWidth);

    ImGui::EndChild();

    ImGui::End();
}

// Function to draw the frame ruler at the top of the timeline
void TimelinePanel::DrawFrameRuler(float availableWidth, float cellWidth) {

    ImDrawList* drawList = ImGui::GetWindowDrawList();
    ImVec2 cursorPos = ImGui::GetCursorScreenPos();
    const float layerNameWidth = m_Appearance.layerNameWidth;
    const float rulerHeight    = m_Appearance.rulerHeight;

    int visibleFrames = std::max(1, (int)(availableWidth / cellWidth)) + 1;

    // Background — covers the pinned name column + visible timeline width
    drawList->AddRectFilled(
        cursorPos,
        ImVec2(cursorPos.x + layerNameWidth + availableWidth, cursorPos.y + rulerHeight),
        m_Appearance.colors.rulerBackground
    );

    // Tick marks and frame numbers for visible frames only
    for (int i = 0; i <= visibleFrames; i++) {
        int   frame = m_FrameOffset + i;
        float x     = cursorPos.x + layerNameWidth + i * cellWidth;

        if (x > cursorPos.x + layerNameWidth + availableWidth) break;

        // Minor tick
        drawList->AddLine(
            ImVec2(x + cellWidth / 2, cursorPos.y + rulerHeight - 4),
            ImVec2(x + cellWidth / 2, cursorPos.y + rulerHeight),
            IM_COL32(100, 100, 100, 255)
        );

        // Major tick + label every 5 frames
        if (frame % 5 == 0) {
            drawList->AddLine(
                ImVec2(x + cellWidth / 2, cursorPos.y + rulerHeight - 8),
                ImVec2(x + cellWidth / 2, cursorPos.y + rulerHeight),
                IM_COL32(150, 150, 150, 255)
            );

            char frameNum[8];
            snprintf(frameNum, sizeof(frameNum), "%d", frame);
            ImVec2 textSize = ImGui::CalcTextSize(frameNum);
            drawList->AddText(
                ImVec2(x + cellWidth / 2 - textSize.x / 2, cursorPos.y + 2),
                IM_COL32(200, 200, 200, 255),
                frameNum
            );
        }
    }

    // Invisible button for ruler scrubbing (skip the pinned name region)
    ImVec2 rulerTimelinePos = ImVec2(cursorPos.x + layerNameWidth, cursorPos.y);
    ImGui::SetCursorScreenPos(rulerTimelinePos);
    ImGui::InvisibleButton("##ruler_seek", ImVec2(availableWidth, rulerHeight));

    if (ImGui::IsItemActive()) {
        float relX = ImGui::GetMousePos().x - rulerTimelinePos.x;
        int   frame = m_FrameOffset + (int)(relX / cellWidth);
        m_CurrentFrame = std::max(0, frame);
    }

    if (ImGui::IsItemHovered() || ImGui::IsItemActive())
        ImGui::SetMouseCursor(ImGuiMouseCursor_ResizeEW);

    // Reset cursor to after the full ruler row
    ImGui::SetCursorScreenPos(ImVec2(cursorPos.x, cursorPos.y + rulerHeight));
}

// Function to draw the layers and keyframes
void TimelinePanel::DrawLayers(float layerNameWidth, float availableWidth, float cellWidth, float rowHeight) {

    ImDrawList* drawList = ImGui::GetWindowDrawList();
    ImVec2 startPos = ImGui::GetCursorScreenPos();

    int visibleFrames = std::max(1, (int)(availableWidth / cellWidth)) + 1;

    for (size_t i = 0; i < m_Layers.size(); i++) {
        ImVec2 rowPos = ImVec2(startPos.x, startPos.y + i * rowHeight);
        const float timelineStartX = rowPos.x + layerNameWidth;

        // --- Pinned layer name column (always at the left edge, never scrolls) ---
        drawList->AddRectFilled(
            rowPos,
            ImVec2(rowPos.x + layerNameWidth, rowPos.y + rowHeight),
            m_Appearance.colors.layerBackground
        );
        drawList->AddRect(
            rowPos,
            ImVec2(rowPos.x + layerNameWidth, rowPos.y + rowHeight),
            m_Appearance.colors.layerBorder
        );
        drawList->AddText(
            ImVec2(rowPos.x + 5, rowPos.y + 5),
            IM_COL32(220, 220, 220, 255),
            m_Layers[i].name.c_str()
        );

        // --- Visible frame cell area background ---
        drawList->AddRectFilled(
            ImVec2(timelineStartX, rowPos.y),
            ImVec2(timelineStartX + availableWidth, rowPos.y + rowHeight),
            m_Appearance.colors.timelineBackground
        );

        const auto& layer      = m_Layers[i];
        const float cellPadding = m_Appearance.cellPadding;

        // --- Keyframe spans (clipped to visible range) ---
        for (size_t k = 0; k < layer.keyframes.size(); k++) {
            const auto& keyframe = layer.keyframes[k];
            int spanStart = keyframe.frame;
            int spanEnd   = (k + 1 < layer.keyframes.size())
                            ? layer.keyframes[k + 1].frame
                            : spanStart + 1; // last keyframe: single-cell span

            // Skip if completely outside the visible window
            if (spanEnd <= m_FrameOffset || spanStart >= m_FrameOffset + visibleFrames)
                continue;

            // Clip span to visible window
            int visStart = std::max(spanStart, m_FrameOffset);
            int visEnd   = std::min(spanEnd,   m_FrameOffset + visibleFrames);

            float startX = timelineStartX + (visStart - m_FrameOffset) * cellWidth;
            float endX   = timelineStartX + (visEnd   - m_FrameOffset) * cellWidth;
            
            /*ImU32 spanColor = keyframe.isTween
                ? m_Appearance.colors.tweenKeyframe
                : m_Appearance.colors.normalKeyframe;
            */
            // If numElements is 0, make it a light gray. If it has at least 1 element, use the normal color, if it's tweened, use the tween color
            ImU32 spanColor;
            if (keyframe.numElements == 0) {
                spanColor = m_Appearance.colors.emptyKeyFrame;
            } else if (keyframe.isTween) {
                spanColor = m_Appearance.colors.tweenKeyframe;
            } else {
                spanColor = m_Appearance.colors.normalKeyframe;
            }

            drawList->AddRectFilled(
                ImVec2(startX + cellPadding, rowPos.y + cellPadding),
                ImVec2(endX   - cellPadding, rowPos.y + rowHeight - cellPadding),
                spanColor
            );
        }

        // --- Grid lines (visible range only) ---
        if (m_Appearance.showGridLines) {
            for (int j = 0; j <= visibleFrames; j++) {
                int   frame = m_FrameOffset + j;
                float x     = timelineStartX + j * cellWidth;
                if (x > timelineStartX + availableWidth) break;

                if (frame % 5 == 0) {
                    drawList->AddLine(ImVec2(x, rowPos.y), ImVec2(x, rowPos.y + rowHeight),
                        m_Appearance.colors.gridLine5Frame, m_Appearance.gridLineThickness5Frame);
                } else {
                    drawList->AddLine(ImVec2(x, rowPos.y), ImVec2(x, rowPos.y + rowHeight),
                        m_Appearance.colors.gridLine, m_Appearance.gridLineThickness);
                }
            }
        }

        // --- Keyframe circles (visible range only) ---
        for (const auto& keyframe : layer.keyframes) {
            if (keyframe.frame < m_FrameOffset || keyframe.frame >= m_FrameOffset + visibleFrames)
                continue;

            float x       = timelineStartX + (keyframe.frame - m_FrameOffset) * cellWidth;
            float circleX = x + cellWidth * 0.5f;
            float circleY = m_Appearance.keyframeCircleCentered
                            ? rowPos.y + rowHeight * 0.5f
                            : rowPos.y + rowHeight - 6.0f;

            drawList->AddCircleFilled(
                ImVec2(circleX, circleY),
                m_Appearance.keyframeCircleRadius,
                 (keyframe.numElements > 0) ? m_Appearance.colors.keyframeCircleFill : IM_COL32(0, 0, 0, 0)
            );
            drawList->AddCircle(
                ImVec2(circleX, circleY),
                m_Appearance.keyframeCircleRadius,
                m_Appearance.colors.keyframeCircleOutline,
                0,
                m_Appearance.keyframeCircleThickness
            );
        }
    }

    // Reserve vertical space so the child window is sized correctly
    ImGui::Dummy(ImVec2(layerNameWidth + availableWidth, m_Layers.size() * rowHeight));
}

void TimelinePanel::DrawPlayhead(float availableWidth, float cellWidth) {
    // Only draw the playhead if it falls within the currently visible frame range
    int visibleFrames = std::max(1, (int)(availableWidth / cellWidth)) + 1;
    if (m_CurrentFrame < m_FrameOffset || m_CurrentFrame >= m_FrameOffset + visibleFrames)
        return;

    ImDrawList* drawList = ImGui::GetWindowDrawList();
    const float layerNameWidth = m_Appearance.layerNameWidth;
    const float rulerHeight    = m_Appearance.rulerHeight;
    const float rowHeight      = m_Appearance.rowHeight;

    // The cursor is currently positioned just after the Dummy in DrawLayers;
    // move back up to the ruler start.
    ImVec2 timelineStart = ImGui::GetCursorScreenPos();
    timelineStart.y -= (m_Layers.size() * rowHeight + rulerHeight);

    float playheadX = timelineStart.x + layerNameWidth
                      + (m_CurrentFrame - m_FrameOffset) * cellWidth
                      + cellWidth / 2.0f;
    float timelineHeight = rulerHeight + m_Layers.size() * rowHeight;

    // Vertical line
    drawList->AddLine(
        ImVec2(playheadX, timelineStart.y + 10),
        ImVec2(playheadX, timelineStart.y + timelineHeight),
        m_Appearance.colors.playhead,
        m_Appearance.playheadThickness
    );

    // Triangle handle
    const float ts = m_Appearance.playheadTriangleSize;
    drawList->AddTriangleFilled(
        ImVec2(playheadX - ts, timelineStart.y + 10),
        ImVec2(playheadX + ts, timelineStart.y + 10),
        ImVec2(playheadX,      timelineStart.y + 15),
        m_Appearance.colors.playhead
    );
}

} // namespace AnimView
