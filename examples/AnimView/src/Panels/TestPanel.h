#pragma once
#include "GUI/GUIHandler.h"

class InspectorPanel : public IPanel {
public:
    void OnImGuiRender() override {
        // The distinct ImGui window logic goes here
        if (!ImGui::Begin("Anim Inspector", &m_IsOpen)) {
            ImGui::End();
            return;
        }

        ImGui::Text("Current Animation: NONE");

        if (ImGui::Button("Load")) {
            // Start animation playback logic
        }
        ImGui::SameLine();
        if (ImGui::Button("Unload")) {
            // Start animation playback logic
        }


        ImGui::Separator();

        ImGui::Text("Playback Controls");
        // Playback controls
        if (ImGui::Button("Play")) {
            // Start animation playback logic
        }
        ImGui::SameLine();
        if (ImGui::Button("Pause")) {
            // Pause animation logic
        }
        ImGui::SameLine();
        if (ImGui::Button("Stop")) {
            // Stop animation logic
        }

        ImGui::Separator();
        ImGui::Text("Duration: 1.5s");

        ImGui::End();
    }
};