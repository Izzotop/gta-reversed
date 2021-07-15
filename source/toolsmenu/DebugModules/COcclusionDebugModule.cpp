#include "StdInc.h"

#include "COcclusionDebugModule.h"
#include "COcclusion.h"
#include "imgui.h"

bool COcclusionDebugModule::DrawActiveOcclusions = false;

void COcclusionDebugModule::ProcessImgui() {
    ImGui::PushItemWidth(365.0f);
    ImGui::InputInt("NumInteriorOcculdersOnMap", &COcclusion::NumInteriorOcculdersOnMap, 1, 100, ImGuiInputTextFlags_ReadOnly);
    ImGui::InputInt("NumOccludersOnMap", &COcclusion::NumOccludersOnMap, 1, 100, ImGuiInputTextFlags_ReadOnly);
    ImGui::InputInt("NumActiveOccluders", &COcclusion::NumActiveOccluders, 1, 100, ImGuiInputTextFlags_ReadOnly);

    ImGui::NewLine();
    ImGui::InputScalar("FarAwayList", ImGuiDataType_::ImGuiDataType_S16, &COcclusion::FarAwayList, nullptr, nullptr, nullptr, ImGuiInputTextFlags_ReadOnly);
    ImGui::InputScalar("NearbyList", ImGuiDataType_::ImGuiDataType_S16, &COcclusion::NearbyList, nullptr, nullptr, nullptr, ImGuiInputTextFlags_ReadOnly);
    ImGui::InputScalar("ListWalkThroughFA", ImGuiDataType_::ImGuiDataType_S16, &COcclusion::ListWalkThroughFA, nullptr, nullptr, nullptr, ImGuiInputTextFlags_ReadOnly);
    ImGui::InputScalar("PreviousListWalkThroughFA", ImGuiDataType_::ImGuiDataType_S16, &COcclusion::PreviousListWalkThroughFA, nullptr, nullptr, nullptr, ImGuiInputTextFlags_ReadOnly);

    ImGui::NewLine();
    ImGui::Checkbox("Draw Active Occlusions", &COcclusionDebugModule::DrawActiveOcclusions);
}
