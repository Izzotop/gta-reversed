/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "Vector.h"
#include "eWeaponType.h"
#include "Entity.h"

class CBulletInfo {
public:
    eWeaponType m_nWeaponType;
    CEntity *m_pCreator;
    int      m_nDestroyTime;
    bool     m_bExists;
    char     _pad0D[3];
    CVector  m_vecPosition;
    CVector  m_vecVelocity;
    short    m_nDamage;
    char     _pad2A[2];

public:
    static void Initialise();
    static void Shutdown();
    static bool AddBullet(CEntity* creator, eWeaponType weaponType, CVector position, CVector velocity);
    static void Update();
};

VALIDATE_SIZE(CBulletInfo, 0x2C);

extern unsigned int MAX_BULLET_INFOS; // default 8
extern CBulletInfo *aBulletInfos; // CBulletInfo aBulletInfos[MAX_BULLET_INFOS]
extern CVector &PlayerSniperBulletStart;
extern CVector &PlayerSniperBulletEnd;