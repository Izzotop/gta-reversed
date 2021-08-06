#pragma once

class CCreepingFire {
public:
    static int8_t(&m_aFireStatus)[32][32];

public:
    static void InjectHooks();
    static void SetReadyToBurn();
    static void Update();
    static int8_t TryToStartFireAtCoors(CVector pos, signed char numGenerations, bool ignored, bool scriptFire, float distance);
};

