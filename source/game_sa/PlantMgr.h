#pragma once

#include "Vector.h"

class CPlantMgr {
public:
    static void InjectHooks();

    static bool Initialise();
    static void Shutdown();
    static void Update(CVector& cameraPosition);
    static void UpdateAmbientColor();
};
