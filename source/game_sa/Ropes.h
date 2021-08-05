/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "Rope.h"


class CRopes
{
public:
    static constexpr int MAX_NUM_ROPES = 8;
    static CRope(&aRopes)[MAX_NUM_ROPES]; // Access using CRopes::GetRope()
    static int& PlayerControlsCrane;

    static void CreateRopeForSwatPed(CVector const& startPos);
    static float FindPickupHeight(CEntity* entity);

    // Returns id to array
    static int FindRope(unsigned int id);
    static void Init();
    static bool IsCarriedByRope(CEntity* entity);

    // Must be used in loop to make attached to holder
    static bool RegisterRope(CEntity* ropeId, unsigned int ropeType, CVector startPos, bool bExpires, unsigned char segmentCount, unsigned char flags, CEntity* holder, unsigned int timeExpire);
    static void Render();
    static void SetSpeedOfTopNode(unsigned int ropeId, CVector dirSpeed);
    static void Shutdown();
    static void Update();
    static bool FindCoorsAlongRope(unsigned int ropeId, float fCoordAlongRope, CVector* pVecPosition, CVector* arg4);

public:
    static inline CRope& GetRope(int index) { return aRopes[index]; }
};
