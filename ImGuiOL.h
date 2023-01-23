#pragma once

#include "imconfig.h"
#ifndef IMGUI_DISABLE


class Context;
class Matrix;

namespace ImGuiOL
{
    //--------- Shortcuts
    void DrawGuizmo(Matrix& mMat);

    //--------- Platform
    void Render(const ImDrawData *pData, Context *pContext);
}



#endif
