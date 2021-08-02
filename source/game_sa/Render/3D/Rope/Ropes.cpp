/*
    Plugin-SDK (Grand Theft Auto San Andreas) source file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#include "StdInc.h"

#include "Ropes.h"

CRope(&CRopes::aRopes)[MAX_NUM_ROPES] = *(CRope(*)[MAX_NUM_ROPES])0xB768B8;
int& CRopes::PlayerControlsCrane = *(int*)0xB76898;

// 0x555DC0
void CRopes::Init()
{
    ((void(__cdecl*)())0x555DC0)();
}

// 0x556B10
void CRopes::Shutdown()
{
    ((void(__cdecl*)())0x556B10)();
}

// 0x558D10
void CRopes::CreateRopeForSwatPed(CVector const& startPos)
{
    ((void(__cdecl*)(CVector const&))0x558D10)(startPos);
}

// 0x556B40
bool CRopes::RegisterRope(CEntity* ropeId, unsigned int ropeType, CVector startPos, bool bExpires, unsigned char segmentCount, unsigned char flags, CEntity* holder, unsigned int timeExpire)
{
    return ((bool(__cdecl*)(CEntity*, unsigned int, CVector, bool, unsigned char, unsigned char, CEntity*, unsigned int))0x556B40)(ropeId, ropeType, startPos, bExpires, segmentCount, flags, holder, timeExpire);
}

// 0x556000
int CRopes::FindRope(unsigned int id)
{
    return ((int(__cdecl*)(unsigned int))0x556000)(id);
}

// 0x556760
float CRopes::FindPickupHeight(CEntity* entity)
{
    return plugin::CallAndReturn<float, 0x556760, CEntity*>(entity);
}

// 0x555E40
bool CRopes::FindCoorsAlongRope(unsigned int ropeId, float fCoorAlongRope, CVector* pVecPosition, CVector* arg4)
{
    return plugin::CallAndReturn<bool, 0x555E40, unsigned int, float, CVector*, CVector*>(ropeId, fCoorAlongRope, pVecPosition, arg4);
}

// 0x555F80
bool CRopes::IsCarriedByRope(CEntity* entity)
{
    return ((bool(__cdecl*)(CEntity*))0x555F80)(entity);
}

// 0x555DF0
void CRopes::SetSpeedOfTopNode(unsigned int ropeId, CVector dirSpeed)
{
    ((void(__cdecl*)(unsigned int, CVector))0x555DF0)(ropeId, dirSpeed);
}

// 0x556AE0
void CRopes::Render()
{
    ((void(__cdecl*)())0x556AE0)();
}

// 0x558D70
void CRopes::Update()
{
    ((void(__cdecl*)())0x558D70)();
}
