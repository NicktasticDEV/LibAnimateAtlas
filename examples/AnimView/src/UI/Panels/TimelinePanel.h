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
    bool isTween = false; // If true, shows purple color; if false, light gray
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
    void DrawFrameRuler(float availableWidth, float cellWidth);
    void DrawLayers(float layerNameWidth, float availableWidth, float cellWidth, float rowHeight);
    void DrawPlayhead(float availableWidth, float cellWidth);
    
    // Timeline state
    int m_CurrentFrame = 0;
    int m_TotalFrames = 120;  // soft playback limit; display extends to last keyframe
    float m_Zoom = 1.0f;
    int m_SelectedLayer = -1;
    int m_FrameOffset = 0;    // first visible frame (Adobe Animate-style panning)
    
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
