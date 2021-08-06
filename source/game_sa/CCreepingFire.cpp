#include "StdInc.h"

int8_t(&CCreepingFire::m_aFireStatus)[32][32] = *(int8_t(*)[32][32])0xB71B68;

void CCreepingFire::InjectHooks()
{
    //ReversibleHooks::Install("CCreepingFire", "SetReadyToBurn", 0x539CC0, &CCreepingFire::SetReadyToBurn);
    //ReversibleHooks::Install("CCreepingFire", "Update", 0x539CE0, &CCreepingFire::Update);
    //ReversibleHooks::Install("CCreepingFire", "TryToStartFireAtCoors", 0x53A450, &CCreepingFire::TryToStartFireAtCoors);
}

void CCreepingFire::SetReadyToBurn()
{
    return plugin::Call<0x539CC0>();
}

void CCreepingFire::Update()
{
    return plugin::Call<0x539CE0>();
}

int8_t CCreepingFire::TryToStartFireAtCoors(CVector pos, signed char numGenerations, bool a5, bool scriptFire, float zDistance)
{
    return plugin::CallAndReturn<int8_t, 0x53A450, CVector, signed char, bool, bool, float>(pos, numGenerations, a5, scriptFire, zDistance);
}
