#include "StdInc.h"

#ifdef EXTRA_DEBUG_FEATURES

#include "COcclusion.h"
#include "imgui.h"

bool COcclusionDebugModule::DrawActiveOcclusions = false;
int COcclusionDebugModule::NumEntitiesSkipped = 0;

void COcclusionDebugModule::ProcessImgui() {
    ImGui::PushItemWidth(300.0f);
    ImGui::InputInt("NumInteriorOcculdersOnMap", &COcclusion::NumInteriorOcculdersOnMap, 1, 100, ImGuiInputTextFlags_ReadOnly);
    ImGui::InputInt("NumOccludersOnMap", &COcclusion::NumOccludersOnMap, 1, 100, ImGuiInputTextFlags_ReadOnly);
    ImGui::InputInt("NumActiveOccluders", &COcclusion::NumActiveOccluders, 1, 100, ImGuiInputTextFlags_ReadOnly);

    ImGui::NewLine();
    ImGui::InputScalar("FarAwayList", ImGuiDataType_::ImGuiDataType_S16, &COcclusion::FarAwayList, nullptr, nullptr, nullptr, ImGuiInputTextFlags_ReadOnly);
    ImGui::InputScalar("NearbyList", ImGuiDataType_::ImGuiDataType_S16, &COcclusion::NearbyList, nullptr, nullptr, nullptr, ImGuiInputTextFlags_ReadOnly);
    ImGui::InputScalar("ListWalkThroughFA", ImGuiDataType_::ImGuiDataType_S16, &COcclusion::ListWalkThroughFA, nullptr, nullptr, nullptr, ImGuiInputTextFlags_ReadOnly);
    ImGui::InputScalar("PreviousListWalkThroughFA", ImGuiDataType_::ImGuiDataType_S16, &COcclusion::PreviousListWalkThroughFA, nullptr, nullptr, nullptr, ImGuiInputTextFlags_ReadOnly);

    ImGui::NewLine();
    ImGui::Text("Num skipped: %d", COcclusionDebugModule::NumEntitiesSkipped);
    COcclusionDebugModule::NumEntitiesSkipped = 0;

    ImGui::NewLine();
    ImGui::Checkbox("Draw Active Occlusions", &COcclusionDebugModule::DrawActiveOcclusions);
}

void COcclusionDebugModule::ProcessRender() {
    if (COcclusionDebugModule::DrawActiveOcclusions
        && COcclusion::NumActiveOccluders > 0) {

        CSprite::FlushSpriteBuffer();
        for (int ind = 0; ind < COcclusion::NumActiveOccluders; ++ind) {
            auto& occl = COcclusion::aActiveOccluders[ind];
            for (auto i = 0; i < occl.m_cLinesCount; ++i) {
                auto& line = occl.m_aLines[i];
                const auto vecEnd = line.m_vecOrigin + line.m_vecDirection * line.m_fLength;
                CLines::ImmediateLine2D(line.m_vecOrigin.x, line.m_vecOrigin.y, vecEnd.x, vecEnd.y, 255, 255, 255, 255, 255, 255, 255, 255);
            }
        }
    }
}
#endif
