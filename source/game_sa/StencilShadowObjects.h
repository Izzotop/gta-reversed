#pragma once

#include "StencilShadowObject.h"

class CStencilShadowObject;

class CStencilShadowObjects {
public:
    static void InjectHooks();

    static void UpdateHierarchy(CStencilShadowObject **firstAvailable, CStencilShadowObject **firstActive, CStencilShadowObject* newOne);
    static void RegisterStencilShadows(RwV3d *cameraPos, int flagDoNotCreateNew);
    static void ScalarConstructor();
    static void ScalarDestructor();
};
