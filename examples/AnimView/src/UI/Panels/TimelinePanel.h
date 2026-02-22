#pragma once

#include "../UILayer.h"
#include <vector>
#include <string>
#include <algorithm>
#include <imgui.h>

namespace AnimView {

// Dummy data structures for timeline visualization
struct Keyframe {
    int frame;
    int numElements = 1;
    bool isTween = false;
};

struct TimelineLayer {
    std::string name;
    std::vector<Keyframe> keyframes;
    bool visible = true;
};

class TimelinePanel : public IPanel {
public:
    TimelinePanel();
    ~TimelinePanel() override = default;

    void OnImGuiRender() override;

private:
    struct DrawContext {
        ImDrawList* drawList   = nullptr;
        float layerNameWidth   = 0.0f;
        float cellWidth        = 0.0f;
        float rowHeight        = 0.0f;
        float availableWidth   = 0.0f;
        int   visibleFrames    = 0;
    };

    // Top-level draw stages (called from OnImGuiRender)
    void DrawFrameRuler(const DrawContext& ctx);
    void DrawLayers(const DrawContext& ctx, int visibleLayers);
    void DrawPlayhead(const DrawContext& ctx, int visibleLayers);

    // Per-layer helpers (called from DrawLayers for each visible row)
    void DrawLayerName(const DrawContext& ctx, const TimelineLayer& layer, ImVec2 rowPos);
    void DrawLayerBackground(const DrawContext& ctx, ImVec2 rowPos);
    void DrawKeyframeSpans(const DrawContext& ctx, const TimelineLayer& layer, ImVec2 rowPos);
    void DrawGridLines(const DrawContext& ctx, ImVec2 rowPos);
    void DrawKeyframeMarkers(const DrawContext& ctx, const TimelineLayer& layer, ImVec2 rowPos);

    // Utility
    ImU32 GetKeyframeSpanColor(const Keyframe& kf) const;
    
    // Timeline state
    int m_CurrentFrame = 0;
    int m_TotalFrames = 120;  // soft playback limit; display extends to last keyframe
    float m_Zoom = 1.0f;
    int m_SelectedLayer = -1;
    int m_FrameOffset = 0;    // first visible frame (Adobe Animate-style panning)
    int m_LayerOffset = 0;    // first visible layer (Adobe Animate-style panning)
    
    // Dummy data - eventually this will come from your animation system
    std::vector<TimelineLayer> m_Layers;
    
public:
    // Appearance Settings  
    struct {
        // Dimensions
        float layerNameWidth = 120.0f;
        float cellWidth = 15.0f;
        float rowHeight = 24.0f;
        float rulerHeight = 24.0f;
        
        // Padding
        float cellPadding = 0.5f;
        
        // Grid
        bool showGridLines = false;
        float gridLineThickness = 1.0f;
        float gridLineThickness5Frame = 1.0f;
        
        // Keyframe markers
        float keyframeCircleRadius = 2.5f;
        float keyframeCircleThickness = 1.0f;
        bool keyframeCircleCentered = false; // If false, circles will be drawn with their top edge on the timeline row
        
        // Playhead
        float playheadThickness = 2.0f;
        float playheadTriangleSize = 6.0f;
        
        // Colors (RGBA)
        struct {
            unsigned int timelineBackground = IM_COL32(50, 50, 50, 255);
            unsigned int rulerBackground = IM_COL32(50, 50, 50, 255);
            unsigned int layerBackground = IM_COL32(50, 50, 50, 255);
            unsigned int layerBorder = IM_COL32(35, 35, 35, 255);
            unsigned int emptyFrame = IM_COL32(45, 45, 45, 255);
            unsigned int emptyFrame5Frame = IM_COL32(58, 58, 58, 255);
            unsigned int emptyKeyFrame = IM_COL32(90, 90, 90, 255);
            unsigned int normalKeyframe = IM_COL32(144, 144, 144, 255);
            unsigned int tweenKeyframe = IM_COL32(124, 93, 162, 255);
            unsigned int gridLine = IM_COL32(35, 35, 35, 255);
            unsigned int gridLine5Frame = IM_COL32(35, 35, 35, 255);
            unsigned int playhead = IM_COL32(70, 160, 255, 175);
            unsigned int keyframeCircleFill = IM_COL32(0, 0, 0, 255);
            unsigned int keyframeCircleOutline = IM_COL32(0, 0, 0, 255);
        } colors;
    } m_Appearance;
};

} // namespace AnimView
