#include "Console.h"
#include <imgui.h>
#include "GR_cross_definitions.h"

namespace gr
{
    Console::Console()
    {
        _p = true;
        _w = true;
        _k = true;
        _e = true;
    }
    
    Console::~Console()
    {
        
    }
    
    void Console::Draw()
    {
        ImGui::Begin("Debug Console");
        ImGui::Checkbox("Info", &_p);
        ImGui::SameLine();
        ImGui::Checkbox("Logs", &_k);
        ImGui::SameLine();
        ImGui::Checkbox("Warning", &_w);
        ImGui::SameLine();
        ImGui::Checkbox("Error", &_e);
        ImGui::Separator();

        if (_p) {
            for (auto e : gr::GetLogBuffer(GR_LOG_TYPE_PRINT))
                ImGui::Text(e.c_str());
        }
        ImGui::Separator();
        if (_k) {
            for (auto e : gr::GetLogBuffer(GR_LOG_TYPE_OK))
                ImGui::TextColored(ImVec4(0, 1, 0, 1), e.c_str());
        }
        ImGui::Separator();
        if (_w) {
            for (auto e : gr::GetLogBuffer(GR_LOG_TYPE_WARNING))
                ImGui::TextColored(ImVec4(1, 1, 0, 1), e.c_str());
        }
        ImGui::Separator();
        if (_e) {
            for (auto e : gr::GetLogBuffer(GR_LOG_TYPE_ERROR))
                ImGui::TextColored(ImVec4(1, 0, 0, 1), e.c_str());
        }

        ImGui::End();
    }
}