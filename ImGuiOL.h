#pragma once

#include "imconfig.h"
#ifndef IMGUI_DISABLE

#include "OL/Math/Color.h"

class Context;
class Matrix;

namespace ImGuiOL
{
    //--------- Shortcuts
    bool ColoredButton(const char* pcName, const ColorRGB& pColor, const ImVec2& vSize = ImVec2(0.f, 0.f), bool bSmall = false);
    bool ColoredSmallButton(const char* pcName, const ColorRGB& pColor);
    void DrawGuizmo(Matrix& mMat);

    //--------- Platform
    void Render(const ImDrawData *pData, Context *pContext);
}



#endif
