#include "imconfig.h"
#ifndef IMGUI_DISABLE

#include "OL/Camera/CameraManager.h"
#include "OL/Math/Matrix.h"

#ifdef PLATFORM_DX12
#include "OL/External/ImGui/backends/imgui_impl_dx12.h"
#include "OL/Render/Context/ContextDX12.h"
#endif

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

//--------------------------------------------------------------------------
//
//--------------------------------------------------------------------------

void ImGuiOL::Render(const ImDrawData* pData, Context* pContext)
{
#ifdef PLATFORM_DX12
    ContextDX12* pContextDX12 = dynamic_cast<ContextDX12*>(pContext);
    ImGui_ImplDX12_RenderDrawData(pData, pContextDX12->GetCommandList());
#else
    AssertToDo;
#endif
}

#endif
