#include "imconfig.h"
#ifndef IMGUI_DISABLE

#include "OL/Camera/CameraManager.h"
#include "OL/Math/Matrix.h"

#include "ImGuizmo.h"

#include "ImGuiOL.h"

//--------------------------------------------------------------------------
//
//--------------------------------------------------------------------------

void ImGuiOL::DrawGuizmo(Matrix& mMat)
{
    static ImGuizmo::OPERATION mCurrentGizmoOperation(ImGuizmo::TRANSLATE);
    static ImGuizmo::MODE mCurrentGizmoMode(ImGuizmo::WORLD);
    if (ImGui::IsKeyPressed(ImGuiKey_ModAlt))
    {
        if (mCurrentGizmoOperation == ImGuizmo::TRANSLATE) mCurrentGizmoOperation = ImGuizmo::ROTATE;
        else if (mCurrentGizmoOperation == ImGuizmo::ROTATE) mCurrentGizmoOperation = ImGuizmo::SCALE;
        else if (mCurrentGizmoOperation == ImGuizmo::SCALE) mCurrentGizmoOperation = ImGuizmo::TRANSLATE;
    }

    const Matrix4 mLookAt = CameraManager::Get()->GetLookAt();
    const Matrix4 mProj = CameraManager::Get()->GetProjection();

    Matrix4 mMat4 = mMat;

    ImGuizmo::SetDrawlist(ImGui::GetForegroundDrawList());
    ImGuizmo::AllowAxisFlip(false);

    ImGuiIO& io = ImGui::GetIO();
    ImGuiViewport* pViewport = ImGui::GetMainViewport();
    ImGuizmo::SetRect(pViewport->Pos.x, pViewport->Pos.y, pViewport->Size.x, pViewport->Size.y);
    ImGuizmo::Manipulate(mLookAt.m_pf, mProj.m_pf, mCurrentGizmoOperation, mCurrentGizmoMode, mMat4.m_pf, NULL, nullptr);

    mMat = mMat4;
}


#endif
