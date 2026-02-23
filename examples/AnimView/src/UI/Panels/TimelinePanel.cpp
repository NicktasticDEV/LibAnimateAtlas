#include "TimelinePanel.h"
#include <imgui.h>
#include <algorithm>

namespace AnimView {

TimelinePanel::TimelinePanel() {

    //Test data for timeline
    //TODO: Replace with actual texture atlas data
    m_Layers = {
        {"Test", {{0, 0, false}, {1, 1, false}, {2, 1, true}, {3, 0, false}, {8, 1, false}, {13, 1, true}, {18, 0, true}, {23, 0, false}}, true},
        {"Test2", {{0, 0, false}, {1, 1, false}, {2, 1, true}, {3, 0, false}, {8, 1, false}, {13, 1, true}, {18, 0, true}, {23, 0, false}}, true},
        {"Test3", {{0, 0, false}, {1, 1, false}, {2, 1, true}, {3, 0, false}, {8, 1, false}, {13, 1, true}, {18, 0, true}, {23, 0, false}}, true},
        {"Test4", {{0, 0, false}, {1, 1, false}, {2, 1, true}, {3, 0, false}, {8, 1, false}, {13, 1, true}, {18, 0, true}, {23, 0, false}}, true},
        {"Test5", {{0, 0, false}, {1, 1, false}, {2, 1, true}, {3, 0, false}, {8, 1, false}, {13, 1, true}, {18, 0, true}, {23, 0, false}}, true},
        {"Test6", {{0, 0, false}, {1, 1, false}, {2, 1, true}, {3, 0, false}, {8, 1, false}, {13, 1, true}, {18, 0, true}, {23, 0, false}}, true},
        {"Test7", {{0, 0, false}, {1, 1, false}, {2, 1, true}, {3, 0, false}, {8, 1, false}, {13, 1, true}, {18, 0, true}, {23, 0, false}}, true},
        {"Test8", {{0, 0, false}, {1, 1, false}, {2, 1, true}, {3, 0, false}, {8, 1, false}, {13, 1, true}, {18, 0, true}, {23, 0, false}}, true},
        {"Test9", {{0, 0, false}, {1, 1, false}, {2, 1, true}, {3, 0, false}, {8, 1, false}, {13, 1, true}, {18, 0, true}, {23, 0, false}}, true},
        {"Test10", {{0, 0, false}, {1, 1, false}, {2, 1, true}, {3, 0, false}, {8, 1, false}, {13, 1, true}, {18, 0, true}, {23, 0, false}}, true},
        {"Test11", {{0, 0, false}, {1, 1, false}, {2, 1, true}, {3, 0, false}, {8, 1, false}, {13, 1, true}, {18, 0, true}, {23, 0, false}}, true},
        {"Test12", {{0, 0, false}, {1, 1, false}, {2, 1, true}, {3, 0, false}, {8, 1, false}, {13, 1, true}, {18, 0, true}, {23, 0, false}}, true},
        {"Test13", {{0, 0, false}, {1, 1, false}, {2, 1, true}, {3, 0, false}, {8, 1, false}, {13, 1, true}, {18, 0, true}, {23, 0, false}}, true},
        {"Test14", {{0, 0, false}, {1, 1, false}, {2, 1, true}, {3, 0, false}, {8, 1, false}, {13, 1, true}, {18, 0, true}, {23, 0, false}}, true},
        {"Test15", {{0, 0, false}, {1, 1, false}, {2, 1, true}, {3, 0, false}, {8, 1, false}, {13, 1, true}, {18, 0, true}, {23, 0, false}}, true},
        {"Test16", {{0, 0, false}, {1, 1, false}, {2, 1, true}, {3, 0, false}, {8, 1, false}, {13, 1, true}, {18, 0, true}, {23, 0, false}}, true},
        {"Test17", {{0, 0, false}, {1, 1, false}, {2, 1, true}, {3, 0, false}, {8, 1, false}, {13, 1, true}, {18, 0, true}, {23, 0, false}}, true},
        {"Test18", {{0, 0, false}, {1, 1, false}, {2, 1, true}, {3, 0, false}, {8, 1, false}, {13, 1, true}, {18, 0, true}, {23, 0, false}}, true},
        {"Test19", {{0, 0, false}, {1, 1, false}, {2, 1, true}, {3, 0, false}, {8, 1, false}, {13, 1, true}, {18, 0, true}, {23, 0, false}}, true},
        {"Test20", {{0, 0, false}, {1, 1, false}, {2, 1, true}, {3, 0, false}, {8, 1, false}, {13, 1, true}, {18, 0, true}, {23, 0, false}}, true}
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

    // Get last keyframe that's in the animation (For knowing what the last keyframe we can scroll to and when the animation ends and shit)
    //TODO: Probably shouldn't be calculated every frame, make it calculate only when animation changes or something
    int lastKeyframe = 0;
    for (const auto& layer : m_Layers) {
        for (const auto& kf : layer.keyframes) {
            lastKeyframe = std::max(lastKeyframe, kf.frame);
        }
    }

    // -------------------------
    // Playback controls
    // -------------------------
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

    // -------------------------
    // Variable calc for timeline
    // -------------------------
    const float layerNameWidth = m_Appearance.layerNameWidth;
    const float cellWidth      = m_Appearance.cellWidth * m_Zoom;
    const float rowHeight      = m_Appearance.rowHeight;
    const float rulerHeight    = m_Appearance.rulerHeight;

    // Available width for the frame grid (excludes the pinned layer-name column)
    float availableWidth = ImGui::GetContentRegionAvail().x - layerNameWidth;
    if (availableWidth < 1.0f) availableWidth = 1.0f;
    int visibleFrames = std::max(1, (int)(availableWidth / cellWidth));

    // Available height for layers (excludes ruler and child border)
    float availableHeight = ImGui::GetContentRegionAvail().y - rulerHeight - 8.0f;
    int visibleLayers = std::max(1, (int)(availableHeight / rowHeight)+1);

    // Horizontal scroll maximum
    int maxFrameOffset = std::max(0, lastKeyframe + 200);
    m_FrameOffset = std::max(0, std::min(m_FrameOffset, maxFrameOffset));

    // Vertical scroll maximum
    int maxLayerOffset = std::max(0, (int)m_Layers.size() - 1);
    m_LayerOffset = std::max(0, std::min(m_LayerOffset, maxLayerOffset));

    // Auto-scroll frame: keep the playhead in view when stepping
    if (m_CurrentFrame < m_FrameOffset) {
        m_FrameOffset = m_CurrentFrame;
    } else if (m_CurrentFrame >= m_FrameOffset + visibleFrames) {
        m_FrameOffset = m_CurrentFrame - visibleFrames + 1;
        m_FrameOffset = std::min(m_FrameOffset, maxFrameOffset);
    }

    // -------------------------
    // Actual timeline thing
    // -------------------------
    // TODO: Add scroll bar
    ImGui::BeginChild("TimelineContent", ImVec2(0, 0), true,
        ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse);

    // Mouse-wheel scroll handling
    if (ImGui::IsWindowHovered()) {
        float wheelH = ImGui::GetIO().MouseWheelH;
        float wheelV = ImGui::GetIO().MouseWheel;
        bool shiftHeld = ImGui::GetIO().KeyShift;

        if (wheelH != 0.0f || (shiftHeld && wheelV != 0.0f)) {
            // Horizontal: pan frames
            float wheel = (wheelH != 0.0f) ? wheelH : wheelV;
            int delta = (wheel > 0) ? 3 : -3;
            m_FrameOffset = std::max(0, std::min(m_FrameOffset + delta, maxFrameOffset));
        } else if (wheelV != 0.0f) {
            // Vertical: pan layers
            int delta = (wheelV > 0) ? -1 : 1;
            m_LayerOffset = std::max(0, std::min(m_LayerOffset + delta, maxLayerOffset));
        }
    }

    // Build a draw context so every helper shares the same layout values
    DrawContext ctx;
    ctx.drawList        = ImGui::GetWindowDrawList();
    ctx.layerNameWidth  = layerNameWidth;
    ctx.cellWidth       = cellWidth;
    ctx.rowHeight       = rowHeight;
    ctx.availableWidth  = availableWidth;
    ctx.visibleFrames   = std::max(1, (int)(availableWidth / cellWidth)) + 1;

    DrawFrameRuler(ctx);
    DrawLayers(ctx, visibleLayers);
    DrawPlayhead(ctx, visibleLayers);

    ImGui::EndChild();

    ImGui::End();
}

// ===========================================================================
// Frame ruler draw
// ===========================================================================
void TimelinePanel::DrawFrameRuler(const DrawContext& ctx) {

    ImVec2 cursorPos = ImGui::GetCursorScreenPos();
    const float rulerHeight = m_Appearance.rulerHeight;

    // -------------------------
    // Tick and frame number drawing
    // -------------------------
    // Background draw
    ctx.drawList->AddRectFilled(
        cursorPos,
        ImVec2(cursorPos.x + ctx.layerNameWidth + ctx.availableWidth, cursorPos.y + rulerHeight),
        m_Appearance.colors.rulerBackground
    );

    // Tick marks and frame numbers
    for (int i = 0; i <= ctx.visibleFrames; i++) {
        int frame = m_FrameOffset + i;
        float x = cursorPos.x + ctx.layerNameWidth + i * ctx.cellWidth;

        if (x > cursorPos.x + ctx.layerNameWidth + ctx.availableWidth) break;

        // Minor tick draw
        ctx.drawList->AddLine(
            ImVec2(x + ctx.cellWidth / 2, cursorPos.y + rulerHeight - 4),
            ImVec2(x + ctx.cellWidth / 2, cursorPos.y + rulerHeight),
            IM_COL32(100, 100, 100, 255)
        );

        // Major tick + frame number draw
        if (frame % 5 == 0) {
            // Major tick draw
            ctx.drawList->AddLine(
                ImVec2(x + ctx.cellWidth / 2, cursorPos.y + rulerHeight - 8),
                ImVec2(x + ctx.cellWidth / 2, cursorPos.y + rulerHeight),
                IM_COL32(150, 150, 150, 255)
            );

            // Frame number draw
            char frameNum[8];
            snprintf(frameNum, sizeof(frameNum), "%d", frame);
            ImVec2 textSize = ImGui::CalcTextSize(frameNum);
            ctx.drawList->AddText(
                ImVec2(x + ctx.cellWidth / 2 - textSize.x / 2, cursorPos.y + 2),
                IM_COL32(200, 200, 200, 255),
                frameNum
            );
        }
    }

    // -------------------------
    // Scrubbing interaction
    // -------------------------
    ImVec2 rulerTimelinePos = ImVec2(cursorPos.x + ctx.layerNameWidth, cursorPos.y);
    ImGui::SetCursorScreenPos(rulerTimelinePos);
    ImGui::InvisibleButton("##ruler_seek", ImVec2(ctx.availableWidth, rulerHeight));

    if (ImGui::IsItemActive()) {
        float relX = ImGui::GetMousePos().x - rulerTimelinePos.x;
        int   frame = m_FrameOffset + (int)(relX / ctx.cellWidth);
        m_CurrentFrame = std::max(0, frame);
    }

    if (ImGui::IsItemHovered() || ImGui::IsItemActive())
        ImGui::SetMouseCursor(ImGuiMouseCursor_ResizeEW);

    // Reset cursor to after the full ruler row
    ImGui::SetCursorScreenPos(ImVec2(cursorPos.x, cursorPos.y + rulerHeight));
}

// ===========================================================================
// Layers draw
// ===========================================================================
void TimelinePanel::DrawLayers(const DrawContext& ctx, int visibleLayers) {

    ImVec2 startPos = ImGui::GetCursorScreenPos();

    int layerEnd = std::min(m_LayerOffset + visibleLayers, (int)m_Layers.size());
    int drawnLayers = std::max(0, layerEnd - m_LayerOffset);

    for (int i = m_LayerOffset; i < layerEnd; i++) {
        int visualRow = i - m_LayerOffset;
        ImVec2 rowPos = ImVec2(startPos.x, startPos.y + visualRow * ctx.rowHeight);

        const auto& layer = m_Layers[i];

        DrawLayerName(ctx, layer, rowPos);
        DrawLayerBackground(ctx, rowPos);
        DrawKeyframeSpans(ctx, layer, rowPos);
        DrawGridLines(ctx, rowPos);
        DrawKeyframeMarkers(ctx, layer, rowPos);
    }

    // Reserve vertical space for only the drawn rows
    ImGui::Dummy(ImVec2(ctx.layerNameWidth + ctx.availableWidth, drawnLayers * ctx.rowHeight));
}

// ===========================================================================
// Per-layer helpers
// ===========================================================================
// Layer name draw
void TimelinePanel::DrawLayerName(const DrawContext& ctx, const TimelineLayer& layer, ImVec2 rowPos) {
    // Background draw
    ctx.drawList->AddRectFilled(
        rowPos,
        ImVec2(rowPos.x + ctx.layerNameWidth, rowPos.y + ctx.rowHeight),
        m_Appearance.colors.layerBackground
    );
    // Border Draw
    ctx.drawList->AddRect(
        rowPos,
        ImVec2(rowPos.x + ctx.layerNameWidth, rowPos.y + ctx.rowHeight),
        m_Appearance.colors.layerBorder
    );
    // Layer type icon draw (placeholder) - replace with actual icons
    ctx.drawList->AddCircleFilled(
        ImVec2(rowPos.x + 15, rowPos.y + ctx.rowHeight / 2),
        8.0f,
        IM_COL32(200, 200, 200, 255)
    );
    // Visibility toggle icon draw aligned to right (placeholder) - replace with actual icons and interaction
    ctx.drawList->AddCircleFilled(
        ImVec2(rowPos.x + ctx.layerNameWidth - 15, rowPos.y + ctx.rowHeight / 2),
        8.0f,
        IM_COL32(200, 200, 200, 255)
    );
    // Layer name draw
    ctx.drawList->AddText(
        ImVec2(rowPos.x + 30, rowPos.y + 5),
        IM_COL32(220, 220, 220, 255),
        layer.name.c_str()
    );
}

// Background fill for the visible frame-cell area
void TimelinePanel::DrawLayerBackground(const DrawContext& ctx, ImVec2 rowPos) {
    const float timelineStartX = rowPos.x + ctx.layerNameWidth;
    ctx.drawList->AddRectFilled(
        ImVec2(timelineStartX, rowPos.y),
        ImVec2(timelineStartX + ctx.availableWidth, rowPos.y + ctx.rowHeight),
        m_Appearance.colors.timelineBackground
    );
}

// Colored keyframe-span rectangles (clipped to visible range)
void TimelinePanel::DrawKeyframeSpans(const DrawContext& ctx, const TimelineLayer& layer, ImVec2 rowPos) {
    const float timelineStartX = rowPos.x + ctx.layerNameWidth;
    const float cellPadding    = m_Appearance.cellPadding;

    for (size_t k = 0; k < layer.keyframes.size(); k++) {
        const auto& keyframe = layer.keyframes[k];
        int spanStart = keyframe.frame;
        int spanEnd = (k + 1 < layer.keyframes.size()) ? layer.keyframes[k + 1].frame : spanStart + 1;

        if (spanEnd <= m_FrameOffset || spanStart >= m_FrameOffset + ctx.visibleFrames) continue;

        int visStart = std::max(spanStart, m_FrameOffset);
        int visEnd = std::min(spanEnd,   m_FrameOffset + ctx.visibleFrames);

        float startX = timelineStartX + (visStart - m_FrameOffset) * ctx.cellWidth;
        float endX = timelineStartX + (visEnd   - m_FrameOffset) * ctx.cellWidth;
        
        ctx.drawList->AddRectFilled(
            ImVec2(startX + cellPadding, rowPos.y + cellPadding),
            ImVec2(endX - cellPadding, rowPos.y + ctx.rowHeight - cellPadding),
            GetKeyframeSpanColor(keyframe)
        );
    }
}

// Vertical grid lines (visible range only)
void TimelinePanel::DrawGridLines(const DrawContext& ctx, ImVec2 rowPos) {
    if (!m_Appearance.showGridLines) return;

    const float timelineStartX = rowPos.x + ctx.layerNameWidth;

    for (int j = 0; j <= ctx.visibleFrames; j++) {
        int frame = m_FrameOffset + j;
        float x = timelineStartX + j * ctx.cellWidth;
        if (x > timelineStartX + ctx.availableWidth) break;

        if (frame % 5 == 0) {
            ctx.drawList->AddLine(
                ImVec2(x, rowPos.y), ImVec2(x, rowPos.y + ctx.rowHeight),
                m_Appearance.colors.gridLine5Frame, m_Appearance.gridLineThickness5Frame
            );
        } else {
            ctx.drawList->AddLine(
                ImVec2(x, rowPos.y), ImVec2(x, rowPos.y + ctx.rowHeight),
                m_Appearance.colors.gridLine, m_Appearance.gridLineThickness
            );
        }
    }
}

// Keyframe circle markers (visible range only)
void TimelinePanel::DrawKeyframeMarkers(const DrawContext& ctx, const TimelineLayer& layer, ImVec2 rowPos) {
    const float timelineStartX = rowPos.x + ctx.layerNameWidth;

    for (const auto& keyframe : layer.keyframes) {
        if (keyframe.frame < m_FrameOffset || keyframe.frame >= m_FrameOffset + ctx.visibleFrames) continue;

        float x = timelineStartX + (keyframe.frame - m_FrameOffset) * ctx.cellWidth;
        float circleX = x + ctx.cellWidth * 0.5f;
        float circleY = m_Appearance.keyframeCircleCentered ? rowPos.y + ctx.rowHeight * 0.5f : rowPos.y + ctx.rowHeight - 6.0f;

        ctx.drawList->AddCircleFilled(
            ImVec2(circleX, circleY),
            m_Appearance.keyframeCircleRadius,
            (keyframe.numElements > 0) ? m_Appearance.colors.keyframeCircleFill : IM_COL32(0, 0, 0, 0)
        );
        ctx.drawList->AddCircle(
            ImVec2(circleX, circleY),
            m_Appearance.keyframeCircleRadius,
            m_Appearance.colors.keyframeCircleOutline,
            0,
            m_Appearance.keyframeCircleThickness
        );
    }
}

// Map a keyframe type to its span color
ImU32 TimelinePanel::GetKeyframeSpanColor(const Keyframe& kf) const {
    if (kf.isTween)           return m_Appearance.colors.tweenKeyframe;
    if (kf.numElements == 0)  return m_Appearance.colors.emptyKeyFrame;
    return m_Appearance.colors.normalKeyframe;
}

// ===========================================================================
// Playhead (vertical line + triangle handle)
// ===========================================================================
void TimelinePanel::DrawPlayhead(const DrawContext& ctx, int visibleLayers) {
    if (m_CurrentFrame < m_FrameOffset || m_CurrentFrame >= m_FrameOffset + ctx.visibleFrames) return;

    const float rulerHeight = m_Appearance.rulerHeight;

    int drawnLayers = std::max(0, std::min(visibleLayers, (int)m_Layers.size() - m_LayerOffset));

    // Back-calculate the ruler start from the Dummy position
    ImVec2 timelineStart = ImGui::GetCursorScreenPos();
    timelineStart.y -= (drawnLayers * ctx.rowHeight + rulerHeight);

    float playheadX = timelineStart.x + ctx.layerNameWidth + (m_CurrentFrame - m_FrameOffset) * ctx.cellWidth + ctx.cellWidth / 2.0f;
    float timelineHeight = rulerHeight + drawnLayers * ctx.rowHeight;

    // Vertical line
    ctx.drawList->AddLine(
        ImVec2(playheadX, timelineStart.y + ctx.rowHeight),
        ImVec2(playheadX, timelineStart.y + timelineHeight),
        m_Appearance.colors.playhead,
        m_Appearance.playheadThickness
    );

    // Triangle handle
    const float ts = m_Appearance.playheadTriangleSize;
    ctx.drawList->AddTriangleFilled(
        ImVec2(playheadX - ts, timelineStart.y + ctx.rowHeight/2),
        ImVec2(playheadX + ts, timelineStart.y + ctx.rowHeight/2),
        ImVec2(playheadX,      timelineStart.y + ctx.rowHeight),
        m_Appearance.colors.playhead
    );

    // Rectangle handle that goes above triangle (to make it easier to grab with mouse)
    ctx.drawList->AddRectFilled(
        ImVec2(playheadX - ts, timelineStart.y + ctx.rowHeight/2),
        ImVec2(playheadX + ts, timelineStart.y - ctx.rowHeight),
        m_Appearance.colors.playhead
    );
}

} // namespace AnimView
