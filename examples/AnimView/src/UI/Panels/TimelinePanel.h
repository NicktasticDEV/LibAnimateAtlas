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
    bool isTween = false; // If true, shows purple color; if false, light gray
};

struct TimelineLayer {
    std::string name;
    std::vector<Keyframe> keyframes;
    bool visible = true;
    bool locked = false;
};

class TimelinePanel : public IPanel {
public:
    TimelinePanel();
    ~TimelinePanel() override = default;

    void OnImGuiRender() override;

private:
    void DrawFrameRuler(float timelineWidth, float cellWidth);
    void DrawLayers(float layerNameWidth, float timelineWidth, float cellWidth, float rowHeight);
    void DrawPlayhead(float timelineWidth, float cellWidth);
    
    // Timeline state
    int m_CurrentFrame = 0;
    int m_TotalFrames = 120;
    float m_Zoom = 1.0f;
    int m_SelectedLayer = -1;
    
    // Dummy data - eventually this will come from your animation system
    std::vector<TimelineLayer> m_Layers;
    
    // Appearance settings
    struct {
        // Dimensions
        float layerNameWidth = 120.0f;
        float cellWidth = 15.0f;
        float rowHeight = 24.0f;
        float rulerHeight = 24.0f;
        
        // Padding
        float cellPadding = 1.0f;
        
        // Grid
        bool showGridLines = false;
        float gridLineThickness = 1.0f;
        float gridLineThickness5Frame = 1.5f;
        
        // Keyframe markers
        float keyframeCircleRadius = 3.5f;
        float keyframeCircleThickness = 1.5f;
        bool keyframeCircleCentered = false; // If false, circles will be drawn with their top edge on the timeline row
        
        // Playhead
        float playheadThickness = 2.0f;
        float playheadTriangleSize = 6.0f;
        
        // Colors (RGBA)
        struct {
            unsigned int rulerBackground = IM_COL32(50, 50, 55, 255);
            unsigned int layerBackground = IM_COL32(55, 55, 60, 255);
            unsigned int layerBorder = IM_COL32(70, 70, 75, 255);
            unsigned int emptyFrame = IM_COL32(60, 60, 65, 255);
            unsigned int normalKeyframe = IM_COL32(200, 200, 200, 255);
            unsigned int tweenKeyframe = IM_COL32(120, 80, 180, 255);
            unsigned int gridLine = IM_COL32(40, 40, 45, 255);
            unsigned int gridLine5Frame = IM_COL32(80, 80, 85, 255);
            unsigned int playhead = IM_COL32(255, 60, 60, 255);
            unsigned int keyframeCircleFill = IM_COL32(30, 30, 35, 255);
            unsigned int keyframeCircleOutline = IM_COL32(255, 255, 255, 255);
        } colors;
    } m_Appearance;
};

} // namespace AnimView
