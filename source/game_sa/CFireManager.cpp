#include "StdInc.h"

CFireManager& gFireManager = *reinterpret_cast<CFireManager*>(0xB71F80);

CFire* CFireManager::FindNearestFire(CVector const& position, bool notBeingExtinguished, bool notScript)
{
    return plugin::CallMethodAndReturn<CFire*, 0x538F40, CFireManager*, CVector const&, bool, bool>(this, position, notBeingExtinguished, notScript);
}

CFire* CFireManager::StartFire(CVector pos, float size, uchar unused, CEntity* creator, uint time, signed char numGenerations, uchar unused_)
{
    return plugin::CallMethodAndReturn<CFire*, 0x539F00, CFireManager*, CVector, float, uchar, CEntity*, uint, signed char, uchar>(this, pos, size, unused, creator, time, numGenerations, unused_);
}
